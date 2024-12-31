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

void	free_commands(t_command *commands)
{
	t_command	*temp;

	while (commands)
	{
		temp = commands->next;
		free_tokens(commands->tokens);
		free(commands);
		commands = temp;
	}
	// need to add close_fd's in here aswell?
}
