#include "minishell.h"

/**
 * wait_for_children - Waits for all child processes to terminate.
 *
 * @shell: Pointer to the shell structure.
 *
 * Loops over all child process IDs stored in `shell->pids` and waits for 
 * each process to terminate using `waitpid()`. Updates the shell's 
 * `exit_code` based on the exit status or termination signal of each 
 * process:
 * - If a child exits normally, the exit status is assigned to 
 *   `shell->exit_code`.
 * - If a child is terminated by a signal, assigns a signal-based 
 *   exit code (e.g., `130` for SIGINT).
 *
 * On `waitpid()` failure, assigns `errno` to `shell->exit_code` and prints 
 * an error message.
 *
 * Returns the final `shell->exit_code` after waiting for all children.
 */
int	wait_for_children(t_mini *shell)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->pids[i], &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_mrworldwide = WTERMSIG(status);
			if (g_mrworldwide == SIGINT)
				shell->exit_code = 130;
		}
		i++;
	}
	return (shell->exit_code);
}

/**
 * Executes a builtin command in a child process.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @is_builtin: Indicates the type of built-in command to execute.
 *
 * Executes the specified built-in command within a forked child process. 
 * Does not handle standard input/output redirection or resetting within this 
 * function; these actions must be managed externally. Exits the process with 
 * `EXIT_SUCCESS` after the built-in command execution.
 */
static void	exec_forked_builtin(t_mini *shell, t_cmd *cmd,
	t_cmd *head, int is_builtin)
{
	if (handle_builtin(is_builtin, shell, head, cmd->cmds) > 0)
		cleanup_failure_child(shell, head, shell->exit_code);
	cleanup_success(shell, head);
	exit(EXIT_SUCCESS);
}

/**
 * exec_forked_cmd - Executes a non-built-in command in a child process.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Resolves the command path using the `get_cmd_path` function and verifies 
 * its accessibility. If the command path is valid, resets signal handlers 
 * and attempts to execute the command using `execve`. 
 * On failure, handles errors, cleans up resources, and exits with an 
 * appropriate error code.
 */
static void	exec_forked_cmd(t_mini *shell, t_cmd *cmd, t_cmd *head)
{
	char	*cmd_path;

	if (!cmd->cmds || !cmd->cmds[0])
		cleanup_failure_child(shell, head, 0);
	cmd_path = get_cmd_path(shell, cmd, cmd->cmds[0]);
	if (!cmd_path)
		check_access(shell, head, cmd->cmds[0]);
	else
		check_access(shell, head, cmd_path);
	sig_reset();
	if (execve(cmd_path, cmd->cmds, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, head, cmd->cmds[0], strerror(errno));
	}
}

/**
 * fork_and_execute - Forks and executes a command in a child process.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Forks the current process to execute the given command. The child process 
 * handles input/output redirection, executes built-in commands, or executes 
 * external commands using `execve`. The parent process keeps track of 
 * child PIDs and handles pipe and file descriptor cleanup.
 *
 * - Detects if the command is a built-in and handles it accordingly.
 * - Sets up signals and redirects file descriptors for the child process.
 * - Executes built-in or non-built-in commands.
 * - Ensures proper error handling, including cleanup on failure.
 *
 * Returns TRUE on success or -1 on fork failure.
 */
int	fork_and_execute(t_mini *shell, t_cmd *cmd, t_cmd *head)
{
	int	is_builtin;

	sig_reset();
	is_builtin = builtins(cmd->cmds[0]);
	shell->pids[cmd->cmd_i] = fork();
	if (shell->pids[cmd->cmd_i] == -1)
	{
		perror("minishell: fork failed");
		return (-1);
	}
	else if (shell->pids[cmd->cmd_i] == 0)
	{
		close_unused_fds(shell, cmd->cmd_i);
		if (!configure_fds_child(shell, cmd))
			cleanup_failure_child(shell, head, shell->exit_code);
		if (!dup_input(shell, cmd, cmd->cmd_i))
			cleanup_failure_child(shell, head, shell->exit_code);
		if (!dup_output(shell, cmd, cmd->cmd_i))
			cleanup_failure_child(shell, head, shell->exit_code);
		if (builtins(cmd->cmds[0]))
			exec_forked_builtin(shell, cmd, head, is_builtin);
		else
			exec_forked_cmd(shell, cmd, head);
	}
	return (TRUE);
}

/**
 * exec_child - Executes a pipeline of commands in child processes.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Initializes a pipeline and iteratively forks child processes to execute 
 * commands. Handles pipe and file descriptor management for each command 
 * in the pipeline. Waits for all child processes to finish and retrieves 
 * the exit status of the last command executed.
 *
 * - Sets up and manages pipes for inter-process communication.
 * - Forks and executes commands with appropriate redirections.
 * - Cleans up file descriptors and waits for all child processes.
 *
 * Returns TRUE on success or FALSE if an error occurs during initialization, 
 * execution, or cleanup.
 */
int	exec_child(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*curr;

	if (!init_pipeline(shell))
		return (FALSE);
	curr = cmd;
	while (curr)
	{
		if (!resolve_heredoc(shell, curr))
			return (FALSE);
		if (fork_and_execute(shell, curr, cmd) == -1)
			return (FALSE);
		sig_child(&sig_handler_child);
		close_extra_fd(curr->input_fd);
		close_fds_and_pipes(shell, curr->cmd_i);
		curr = curr->next;
	}
	shell->exit_code = wait_for_children(shell);
	cleanup_success(shell, cmd);
	return (TRUE);
}
