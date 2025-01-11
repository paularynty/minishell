#include "minishell.h"

/**
 * configure_fds - Resolves file descriptors for input and output redirection.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Processes input and output redirections specified in the command using 
 * `handle_redirection()`. If no redirection is specified, sets the input file 
 * descriptor to `STDIN_FILENO` and the output file descriptor to 
 * `STDOUT_FILENO`.
 *
 * Returns TRUE on success or FALSE if redirection processing fails.
 * */
int	configure_fds(t_mini *shell, t_cmd *cmd)
{
	if (!handle_redirection(shell, cmd))
		return (FALSE);
	if (cmd->input_fd == -1)
		cmd->input_fd = STDIN_FILENO;
	if (cmd->output_fd == -1)
		cmd->output_fd = STDOUT_FILENO;
	return (TRUE);
}

/**
 * dup_input - Duplicates and redirects the input file descriptor.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @i: Index of the current command in the pipeline.
 *
 * Handles input redirection for a command:
 * - If `cmd->input_fd` is not `STDIN_FILENO`, redirects it using `dup2()` 
 *   and closes the previous input file descriptor.
 * - Otherwise, if the command is part of a pipeline, redirects the read end 
 *   of the pipe from the previous command to `STDIN_FILENO`.
 * - Closes the corresponding pipe read end after duplication.
 *
 * Prints an error message and updates the shell's `exit_code` if the 
 * redirection or duplication fails.
 *
 * Returns TRUE on success or FALSE on failure.
 */
int	dup_input(t_mini *shell, t_cmd *cmd, int i)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (!dup2_close(cmd->input_fd, STDIN_FILENO))
		{
			perror("dup2 failed for input redirection");
			shell->exit_code = 1;
			return (FALSE);
		}
		if (i > 0)
			close(shell->pipes[i - 1][0]);
	}
	else if (i > 0)
	{
		if (!dup2_close(shell->pipes[i - 1][0], STDIN_FILENO))
		{
			perror("dup2 failed for pipe input");
			shell->exit_code = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

/**
 * dup_output - Duplicates and redirects the output file descriptor.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @i: Index of the current command in the pipeline.
 *
 * Handles output redirection for a command:
 * - If `cmd->output_fd` is not `STDOUT_FILENO`, redirects it using `dup2()` 
 *   and closes the previous output file descriptor.
 * - Otherwise, if the command is part of a pipeline, redirects the write 
 *   end of the pipe to `STDOUT_FILENO`.
 * - Closes the corresponding pipe write end after duplication.
 *
 * Prints an error message and updates the shell's `exit_code` if the 
 * redirection or duplication fails.
 *
 * Returns TRUE on success or FALSE on failure.
 */
int	dup_output(t_mini *shell, t_cmd *cmd, int i)
{
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (!dup2_close(cmd->output_fd, STDOUT_FILENO))
		{
			perror("dup2 failed for output redirection");
			shell->exit_code = 1;
			return (FALSE);
		}
		if (i < shell->cmd_count - 1)
			close(shell->pipes[i][1]);
	}
	else if (i < shell->cmd_count - 1)
	{
		if (!dup2_close(shell->pipes[i][1], STDOUT_FILENO))
		{
			perror("dup2 failed for pipe output");
			shell->exit_code = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

/**
 * dup2_close - Duplicates a file descriptor and closes the old descriptor.
 *
 * @old_fd: File descriptor to duplicate.
 * @new_fd: Target file descriptor for duplication.
 *
 * Uses `dup2()` to duplicate `old_fd` to `new_fd`. Closes `old_fd` after 
 * successful duplication. If `old_fd` is invalid or the duplication fails, 
 * closes `old_fd` and prints an error message to `stderr`.
 *
 * Returns TRUE on success or FALSE on failure.
 */
int	dup2_close(int old_fd, int new_fd)
{
	if (old_fd < 0)
	{
		ft_putstr_fd("minishell: invalid file descriptor\n", 2);
		return (FALSE);
	}
	if (dup2(old_fd, new_fd) == -1)
	{
		close(old_fd);
		return (FALSE);
	}
	close(old_fd);
	return (TRUE);
}
