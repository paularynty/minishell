#include "minishell.h"

/* If memory allocation for 2D pipe array fails at any point,
free all previously pipes allocated. */
void	free_pipes(t_mini *shell, int i)
{
	while (i > 0)
	{
		i--;
		free(shell->pipes[i]);
	}
	free(shell->pipes);
	shell->pipes = NULL;
}

void	close_all_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

static void	clean_tokens(t_token *tokens) 
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
		temp = NULL;
    }
}

void	clean_commands(t_cmd *cmd) 
{
	t_cmd	*temp;

	while (cmd)
	{
		clean_tokens(cmd->tokens);
		cmd->tokens = NULL;
		cmd->next = NULL;
		temp = cmd;
		cmd = cmd->next;
		free(temp);
		temp = NULL;
    }
}

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
	//unlink all heredocs;
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	//clean commands;
	//free pids;
	//if there is more than 1 command, ft_free_array for however many cmd->cmds arrays there are
	//cleanup_shell(shell);
	// free(shell);
	// shell = NULL;
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
void	cleanup_success(t_mini *shell)
{
	int	i;

	i = shell->cmd_count - 2;
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
}

void	cleanup(t_mini *shell)
{
	ft_free_array(&shell->env);
	// ft_free_array(&shell->cmd);
	// free(shell->input);
	// shell->input = NULL;
	free(shell->cwd);
	shell->cwd = NULL;
	shell->heredoc = NULL;
	// clean_commands(command);
}
