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

int	resolve_input_fd(t_mini *shell, t_command *cmd, t_token *token)
{
//	check_print("Entering resolve_input_fd: token type = %d\n", token->type);
	if (cmd->input_fd != -1)
	{
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (token->type == REDIR_IN)
		cmd->input_fd = open_infile(shell, token->next->value);
	else if (token->type == HEREDOC)
		cmd->input_fd = handle_heredoc(token->next->value);
	if (cmd->input_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	resolve_output_fd(t_mini *shell, t_command *cmd, t_token *token)
{
	check_print("Entering resolve_output_fd: token type = %d\n", token->type);
	if (cmd->output_fd != -1)
	{
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
	if (token->type == REDIR_OUT)
	{
		debug_print("Opening output file %s\n", token->next->value);
		cmd->output_fd = open_outfile(shell, token->next->value);
	}
	else if (token->type == REDIR_APPEND)
		cmd->output_fd = open_append_file(shell, token->next->value);
	if (cmd->output_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	process_redir(t_mini *shell, t_command *cmd)
{
	t_token	*token;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
		{
			if (!resolve_input_fd(shell, cmd, token))
			{
				close_fd_if_needed(cmd->output_fd);
				return (FALSE);
			}
		}
		else if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
		{
			if (!resolve_output_fd(shell, cmd, token))
			{
				close_fd_if_needed(cmd->input_fd);
				return (FALSE);
			}
		}
		token = token->next;
	}
	return (TRUE);
}