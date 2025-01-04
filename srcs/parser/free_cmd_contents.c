#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token		*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*temp;

	while (cmds)
	{
		temp = cmds->next;
		free_tokens(cmds->tokens);
		free_2d_array(cmds->cmd);
		free(cmds);
		cmds = temp;
	}
	// need to add close_fd's in here aswell?
}
