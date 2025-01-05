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

void	free_commands(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		free_tokens(cmd->tokens);
		free_2d_array(cmd->cmds);
		free(cmd);
		cmd = temp;
	}
	// need to add close_fd's in here aswell?
}
