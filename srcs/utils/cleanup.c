#include "minishell.h"

/**
 * Cleans up resources and exits the shell on failure.
 *
 * @shell: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * @ex: Exit status code to terminate the shell with.
 *
 * This function performs a comprehensive cleanup, including closing file
 * descriptors, unlinking heredocs, freeing memory, and releasing resources
 * before terminating the shell with the specified exit status.
 */
void	cleanup_failure(t_mini *shell, t_cmd *cmd)
{
	int	i;

	i = shell->cmd_count - 2;
	if (shell->pipes)
	{
		close_all_pipes(shell);
		free_pipes(shell, i);
	}
	free(shell->pids);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	if (cmd)
		clean_commands(cmd);
	free_null(&shell->cwd);
}

/**
 * If a child process fails, cleans up resources and
 * exits the child process with the respective exit status.
 *
 * @shell: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * @exit_status: Exit status code to exit the child process with.
 *
 * This function performs a comprehensive cleanup, including closing file
 * descriptors, unlinking heredocs, freeing memory, and releasing resources
 * before terminating the shell with the specified exit status.
 */
void	cleanup_failure_child(t_mini *shell, t_cmd *cmd, int exit_status)
{
	int	i;

	i = shell->cmd_count - 2;
	close_all_pipes(shell);
	if (shell->pipes)
		free_pipes(shell, i);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	free(shell->pids);
	if (cmd)
		clean_commands(cmd);
	ft_free_array(&shell->env);
	free_null(&shell->cwd);
	exit(exit_status);
}

/**
 * cleanup_success - Cleans up resources upon successful child process
 * execution.
 *
 * @shell: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * 
 */
void	cleanup_success(t_mini *shell, t_cmd *cmd)
{
	int	i;

	i = shell->cmd_count - 2;
	if (shell->pids)
	{
		free(shell->pids);
		shell->pids = NULL;
	}
	close_all_pipes(shell);
	if (shell->pipes)
		free_pipes(shell, i);
	if (cmd)
		clean_commands(cmd);
	// free_null(&shell->cwd);
	shell->cmd_count = 0;
}

void	cleanup_success_child(t_mini *shell, t_cmd *cmd)
{
	int	i;

	i = shell->cmd_count - 2;
	if (shell->pids)
	{
		free(shell->pids);
		shell->pids = NULL;
	}
	close_all_pipes(shell);
	if (shell->pipes)
		free_pipes(shell, i);
	if (cmd)
		clean_commands(cmd);
	ft_free_array(&shell->env);
	free_null(&shell->cwd);
	shell->cmd_count = 0;
}

/**
 * cleanup_success - Cleans up resources upon successful child process
 * execution.
 *
 * @shell: Pointer to the shell structure containing resources to free.
 * @i: Index of the current command being executed.
 * 
 */
void	cleanup_success_exit(t_mini *shell, t_cmd *cmd)
{
	int	i;
	int	j;

	ft_free_array(&shell->env);
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
		free_pipes(shell, j);
	}
	if (cmd)
		clean_commands(cmd);
	free_null(&shell->cwd);
	shell->cmd_count = 0;
}
