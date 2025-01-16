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
	while (i >= 0)
	{
		free(shell->pipes[i]);
		i--;
	}
	free(shell->pipes);
	shell->pipes = NULL;
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
