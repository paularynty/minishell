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

static void	close_fd_if_needed(int fd)
{
	if (fd > 2)
		close(fd);
}

int	resolve_input_fd(t_mini *shell, t_command *cmd, int *input_fd)
{
	if (*input_fd != -1)
	{
		close(*input_fd);
		*input_fd = -1;
	}
	if (cmd->tokens->type == REDIR_IN)
		*input_fd = open_infile(shell, cmd->tokens->value);
	// else if (cmd->tokens->type == HEREDOC)
	// 	*input_fd = open_heredoc(cmd, cmd->heredoc_name);
	if (*input_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	resolve_output_fd(t_mini *shell, t_command *cmd, int *output_fd)
{
	if (*output_fd != -1)
	{
		close(*output_fd);
		*output_fd = -1;
	}
	if (cmd->tokens->type == REDIR_OUT)
		*output_fd = open_outfile(shell, cmd->tokens->next->value);
	else if (cmd->tokens->type == REDIR_APPEND)
		*output_fd = open_append_file(shell, cmd->tokens->next->value);
	if (*output_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	process_redir(t_mini *shell, t_command *cmd, 
	int *input_fd, int *output_fd)
{
	t_token	*token;

	token = cmd->tokens;
	while (token)
	{
		if (cmd->tokens->type == REDIR_IN || cmd->tokens->type == HEREDOC)
		{
			if (!resolve_input_fd(shell, cmd, input_fd))
			{
				close_fd_if_needed(*output_fd);
				return (FALSE);
			}
		}
		else if (cmd->tokens->type == REDIR_OUT 
			|| cmd->tokens->type == REDIR_APPEND)
		{
			if (!resolve_output_fd(shell, cmd, output_fd))
			{
				close_fd_if_needed(*input_fd);
				return (FALSE);
			}
		}
		token = token->next;
	}
	return (TRUE);
}

