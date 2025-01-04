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

void	free_commands(t_cmd *commands)
{
	t_cmd	*temp;

	while (commands)
	{
		temp = commands->next;
		free_tokens(commands->tokens);
		free_2d_array(commands->cmd);
		free(commands);
		commands = temp;
	}
	// need to add close_fd's in here aswell?
}
