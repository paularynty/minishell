#include "minishell.h"

void	free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

/* If memory allocation for 2D pipe array fails at any point,
free all previously allocated pipes. */
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
		temp = tokens->next;
		free(tokens->value);
		tokens->value = NULL;
		free(tokens);
		tokens = temp;
	}
}

void	clean_commands(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		clean_tokens(cmd->tokens);
		cmd->tokens = NULL;
		ft_free_array(&cmd->cmds);
		free(cmd);
		cmd = temp;
	}
}

// void	clean_commands(t_cmd *cmd)
// {
// 	t_cmd	*temp;

// 	temp = NULL;
// 	if (!cmd->next)
// 	{
// 		clean_tokens(cmd->tokens);
// 		cmd->tokens = NULL;
// 		ft_free_array(&cmd->cmds);
// 		free(cmd);
// 	}
// 	else
// 	{
// 		while (cmd)
// 		{
// 			temp = cmd->next;
// 			clean_tokens(cmd->tokens);
// 			cmd->tokens = NULL;
// 			ft_free_array(&cmd->cmds);
// 			free(cmd);
// 			cmd = temp;
// 		}
// 	}
// }

// static void	clean_tokens(t_token *tokens)
// {
// 	t_token	*temp;

// 	while (tokens)
// 	{
// 		temp = tokens;
// 		tokens = tokens->next;
// 		free(temp->value);
// 		free(temp);
// 		temp = NULL;
// 	}
// }

// void	clean_commands(t_cmd *cmd)
// {
// 	t_cmd	*temp;

// 	while (cmd)
// 	{
// 		ft_free_array(&cmd->cmds);
// 		clean_tokens(cmd->tokens);
// 		cmd->tokens = NULL;
// 		cmd->next = NULL;
// 		temp = cmd;
// 		cmd = cmd->next;
// 		free(temp);
// 		temp = NULL;
// 	}
// }
