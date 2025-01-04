#include "minishell.h"
static void	clean_tokens(t_token *tokens) 
{
	t_token *temp;
	
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
