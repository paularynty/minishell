#include "minishell.h"

/**
 * cleanup_failure - Cleans up resources and exits the shell on failure.
 *
 * @shell: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * @ex: Exit status code to terminate the shell with.
 *
 * This function performs a comprehensive cleanup, including closing file
 * descriptors, unlinking heredocs, freeing memory, and releasing resources
 * before terminating the shell with the specified exit status.
 */
void	cleanup_failure(t_mini *shell, t_cmd *cmd, int ex)
{
	close_all_pipes(shell);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	free(shell->pids);
	cleanup(shell, cmd);
	//if there is more than 1 command, ft_free_array for however many cmd->cmds arrays there are
	//cleanup_shell(shell);
	// free(shell);
	// shell = NULL;
	// shell->cmd_count = 0;
	exit(ex);
}

/**
 * cleanup_success - Cleans up resources
 * and exits the shell with the given status upon success.
 *
 * @shell: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * @exit_status: Exit status code to terminate the shell with.
 */
void	cleanup_success(t_mini *shell, t_cmd *cmd)
{
	int	i;
	int	j;

	i = shell->cmd_count - 2;
	j = i;
	if (shell->pids)
	{
		free(shell->pids);
		shell->pids = NULL;
	}
	if (shell->cmd_count > 1 && shell->pipes)
	{
		if (shell->pipes[i][0] != -1)
		{
			if (shell->pipes[i][0] > 0)
				close(shell->pipes[i][0]);
		}
	}
	free_pipes(shell, j);
	cleanup(shell, cmd);
}

void	cleanup(t_mini *shell, t_cmd *cmd)
{
	// if (shell->env)
	// 	ft_free_array(&shell->env);
	if (cmd)
		clean_commands(cmd);
	free_null(&shell->cwd);
	shell->heredoc = NULL;
}
