#include "minishell.h"

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
static void	exec_forked_builtin(t_mini *shell, t_cmd *cmd, t_cmd *head, int is_builtin)
{
	// handle_builtin(is_builtin, shell, cmd);
	if (handle_builtin(is_builtin, shell, cmd) > 0)
		cleanup_failure(shell, head, shell->exit_code); // modified cmd -> head
	cleanup_success(shell, head); // modified cmd -> head
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
static void	exec_forked_cmd(t_mini *shell, t_cmd *cmd, t_cmd *head) // added head for potential cleanup
{
	char	*cmd_path;

	if (!cmd->cmds || !cmd->cmds[0])
		cleanup_failure(shell, head, 0);
	// printf("cmd: %s\n", cmd->cmds[0]);
	cmd_path = get_cmd_path(shell, cmd, cmd->cmds[0]);
	// printf("cmd path: %s\n", cmd_path);
	if (!cmd_path)
		check_access(shell, head, cmd->cmds[0]); // modified cmd -> head for potential cleanup
	else
		check_access(shell, head, cmd_path); // modified cmd -> head for potential cleanup
	signal_reset();
	if (execve(cmd_path, cmd->cmds, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, head, cmd->cmds[0], strerror(errno), errno);
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
int	fork_and_execute(t_mini *shell, t_cmd *cmd, t_cmd *head) // added head (for potential cleanup)
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
		if (!configure_fds_child(shell, cmd))
		{
			cleanup_failure(shell, head, shell->exit_code); // modified cmd -> head
			return (FALSE);
		}
		if (!dup_input(shell, cmd, cmd->cmd_i))
			cleanup_failure(shell, head, shell->exit_code); // modified cmd -> head
		if (!dup_output(shell, cmd, cmd->cmd_i))
			cleanup_failure(shell, head, shell->exit_code); // modified cmd -> head
		if (builtins(cmd->cmds[0]))
			exec_forked_builtin(shell, cmd, head, is_builtin); // added head to the function call
		else
			exec_forked_cmd(shell, cmd, head); // added head to the function call
	}
	return (TRUE);
}

static int	resolve_heredoc(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;
	int		i;

	token = cmd->tokens;
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (cmd->input_fd != -1)
			{
				close(cmd->input_fd);
				cmd->input_fd = -1;
			}
			cmd->input_fd = handle_heredoc(shell, token->next->value);
			if (cmd->input_fd == -1)
				return (FALSE); // pipe_error
			cmd->heredoc_i = i;
		}
		token = token->next;
		i++;
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
			return (FALSE); // cleanup && return
		if (fork_and_execute(shell, curr, cmd) == -1)
			return (FALSE); // cleanup && return
		close_extra_fd(curr->input_fd);
		close_fds_and_pipes(shell, curr->cmd_i);
		curr = curr->next;
	}
	shell->exit_code = wait_for_children(shell);
	cleanup_success(shell, cmd);
	signal_init();
	return (TRUE);
}
