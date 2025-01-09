#include "minishell.h"

/**
 * exec_forked_builtin - Executes a built-in command in a child process.
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
static void	exec_forked_builtin(t_mini *shell, t_cmd *cmd, int is_builtin)
{
	// if (!save_std(shell))
	// 	debug_print("Failed to save std\n");
	handle_builtin(is_builtin, shell, cmd); //rework this to take in account failed builtin exec
	// if (!reset_std(shell))
	// 	debug_print("Failed to reset std\n");
	// cleanup_success(shell);
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
 * appropriate error code. If `execve` succeeds, the process exits with `EXIT_SUCCESS`.
 */
static void	exec_forked_cmd(t_mini *shell, t_cmd *cmd)
{
	char	*cmd_path;
	
	cmd_path = get_cmd_path(shell, cmd->cmds[0]);
	if (!cmd_path)
		check_access(shell, cmd->cmds[0]);
	else
		check_access(shell, cmd_path);
	signal_reset();
	debug_print("sending to execve: %s %s\n", cmd->cmds[0], cmd->cmds[1]);
	if (execve(cmd_path, cmd->cmds, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, cmd->cmds[0], strerror(errno), errno);
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
int	fork_and_execute(t_mini *shell, t_cmd *cmd)
{
	int	is_builtin;

	is_builtin = builtins(cmd->cmds[0]);
	signal_reset();
	shell->pids[cmd->cmd_i] = fork();
	if (shell->pids[cmd->cmd_i] == -1)
	{
		perror("minishell: fork failed");
		return (-1);
	}
	else if (shell->pids[cmd->cmd_i] == 0)
	{
		signal_child();
		close_unused_fds(shell, cmd->cmd_i);
		if (!resolve_fds(shell, cmd))
		{
			cleanup_failure(shell, cmd, shell->exit_code);
			return (FALSE);
		}
		if (!dup_input(shell, cmd, cmd->cmd_i))
			cleanup_failure(shell, cmd, shell->exit_code);
		if (!dup_output(shell, cmd, cmd->cmd_i))
			cleanup_failure(shell, cmd, shell->exit_code);
		if (builtins(cmd->cmds[0])) //check for builtin cmd in pipe
			exec_forked_builtin(shell, cmd, is_builtin);
		else
			exec_forked_cmd(shell, cmd);
	}
	return (TRUE);
}

/**
 * exec_parent - Executes a built-in command in the parent process.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @is_builtin: Indicates the type of built-in command to execute.
 *
 * Executes a built-in command directly in the parent process, handling 
 * input/output redirection and resetting file descriptors upon completion. 
 * Updates the shell's exit code based on the outcome of the execution. 
 * If any part of the execution process (e.g., file descriptor redirection or 
 * saving/resetting std) fails, the function returns FALSE.
 *
 * Returns TRUE on success or FALSE on failure.
 */
static int	exec_parent(t_mini *shell, t_cmd *cmd, int is_builtin)
{
	if (!resolve_fds(shell, cmd) || !save_std(shell, cmd))
	{
		shell->exit_code = 1; //check if this is correct, or if I should just carry over whatever exit code my builtin cmd returns
		return (FALSE);
	}
	if (!redirect_fd(cmd->input_fd, STDIN_FILENO) || !redirect_fd(cmd->output_fd, STDOUT_FILENO))
		return (FALSE);
	if (handle_builtin(is_builtin, shell, cmd) > 0)
	{
		reset_std(shell, cmd);
		return (FALSE);
	}
	if (cmd->input_fd != STDIN_FILENO || cmd->output_fd != STDOUT_FILENO)
	{
		if (!reset_std(shell, cmd))
			return (FALSE);
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
static int	exec_child(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*curr;

	if (!init_pipeline(shell))
		return (FALSE);
	curr = cmd;
	while (curr)
	{
		if (fork_and_execute(shell, curr) == -1)
			return (FALSE);
		close_fds_and_pipes(shell, curr->cmd_i);
		curr = curr->next;
	}
	shell->exit_code = wait_for_children(shell);
	signal_init();
	cleanup_success(shell);
	return (TRUE);
}

/**
 * execute - Executes the given command(s).
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the first command structure.
 *
 * Determines whether the command is a builtin and, if so, whether it can 
 * be executed directly in the parent process. If the command is not a 
 * built-in or if there are multiple commands (pipeline), delegates execution 
 * to `exec_child`, which handles forking and executing child processes.
 *
 * - For a single built-in command, executes it in the parent process and 
 *   updates the shell's exit code.
 * - For pipelines or external commands, forks child processes for execution.
 * - Ensures proper error handling for both built-in and external commands.
 *
 * Returns the shell's updated exit code.
 */
int	execute(t_mini *shell, t_cmd *cmd)
{
	int			is_builtin;

	is_builtin = builtins(cmd->cmds[0]);
	if (shell->cmd_count == 1 && is_builtin)
	{
		if (!exec_parent(shell, cmd, is_builtin))
			return (shell->exit_code);
		shell->exit_code = 0;
		return (shell->exit_code);
	}
	else
		exec_child(shell, cmd); // what if it fails?
	return (shell->exit_code);
}
