#include "minishell.h"

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
	if (!configure_fds(shell, cmd) || !save_std(shell, cmd))
	{
		clean_commands(cmd);
		return (FALSE);
	}
	if (!redirect_fd(cmd->input_fd, STDIN_FILENO)
		|| !redirect_fd(cmd->output_fd, STDOUT_FILENO))
		return (FALSE);
	if (handle_builtin(is_builtin, shell, cmd) > 0)
	{
		reset_std(shell, cmd);
		clean_commands(cmd);
		return (FALSE);
	}
	if (cmd->input_fd != STDIN_FILENO || cmd->output_fd != STDOUT_FILENO)
	{
		if (!reset_std(shell, cmd))
			return (FALSE);
	}
	cleanup_success(shell, cmd);
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
	{
		if (!exec_child(shell, cmd))
			cleanup_failure(shell, cmd, shell->exit_code);
	}
	return (shell->exit_code);
}
