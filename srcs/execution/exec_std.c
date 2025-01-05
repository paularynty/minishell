#include "minishell.h"

/**
 * save_fds - Saves the current standard input/output file descriptors.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * If the input or output file descriptors are redirected, duplicates the
 * current STDIN_FILENO and STDOUT_FILENO file descriptors to save their
 * states. Updates `mini->stdin_saved` and `mini->stdout_saved` respectively.
 * Returns 0 on success or 1 on failure with an updated exit status.
 */
int	save_std(t_mini *shell, t_cmd *cmd)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		cmd->saved_stdin = dup(STDIN_FILENO);
		if (cmd->saved_stdin == -1)
		{
			shell->exit_code = 1;
			return (perror("minishell: failed to save stdin\n"), FALSE);
		}
	}
	if (cmd->output_fd != STDOUT_FILENO)
	{
		cmd->saved_stdout = dup(STDOUT_FILENO);
		if (cmd->saved_stdout == -1)
		{
			shell->exit_code = 1;
			return (perror("minishell: failed to save stdout\n"), FALSE);
		}
	}
	return (TRUE);
}

int	reset_std(t_mini *shell, t_cmd *cmd)
{
	if (cmd->saved_stdin != -1 && cmd->saved_stdin != STDIN_FILENO)
	{
		if (dup2_close(cmd->saved_stdin, STDIN_FILENO))
		{
			perror("minishell: failed to restore original stdin\n");
			shell->exit_code = 1;
			cmd->saved_stdin = -1;
			return (FALSE);
		}
		cmd->saved_stdin = -1;
	}
	if (cmd->saved_stdout != -1 && cmd->saved_stdout != STDOUT_FILENO)
	{
		if (dup2_close(cmd->saved_stdout, STDOUT_FILENO))
		{
			perror("minishell: failed to restore original stdout\n");
			shell->exit_code = 1;
			cmd->saved_stdout = -1;
			return (FALSE);
		}
		cmd->saved_stdout = -1;
	}
	return (TRUE);
}
