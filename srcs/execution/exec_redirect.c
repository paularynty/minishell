#include "minishell.h"

// int	handle_heredoc(t_mini *shell, t_command *command)
// {
// 	char *line;

// 	if (command->tokens->type == HEREDOC)
// 		line = readline("> ");	
// 	return (TRUE);
// }

// int	handle_input(t_command *cmd, int *error)
// {
// 	t_token	*token;
// 	int		fd;

// 	fd = -1;
// 	token = cmd->tokens;
// 	while (token)
// 	{
// 		if (token->type == REDIRECT_IN)
// 			fd = open(cmd->tokens->next->value, O_RDONLY);
// 	//	else if (token->type == HEREDOC)
// 		//	fd = handle_heredoc(cmd->token->next->value);
// 		token = token->next;
// 	}
// 	return (fd);
// }

// int	handle_output(t_command *cmd, int *error)
// {
// 	t_token	*token;
// 	int		fd;

// 	token = cmd->tokens;
// 	while (token)
// 	{
// 		if (token->type == REDIRECT_OUT)
// 		{
// 			fd = open(cmd->tokens->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 				*error = errno;
// 		}
// 		else if (cmd->tokens->type == REDIRECT_APPEND)
// 		{
// 			fd = open(cmd->tokens->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (fd == -1)
// 				*error = errno;
// 		}
// 		// if (*error)
// 		//	strerrorilla error viesti ja exit coodia talteen johonkin? Ei exitata koska ei olla forkattu
// 		token = token->next;
// 	}
// 	return (fd);
// }