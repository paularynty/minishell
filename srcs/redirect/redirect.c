#include "minishell.h"

static void	close_fd_if_needed(int fd)
{
	if (fd > 2)
		close(fd);
}

int	redirect_fd(int src_fd, int dest_fd)
{
	if (src_fd != dest_fd)
	{
		if (dup2(src_fd, dest_fd) == -1)
		{
			perror("dup2 failed");
			close(src_fd);
			return (FALSE);
		}
		close(src_fd);
	}
	return (TRUE);
}

int	resolve_input_fd(t_mini *shell, t_cmd *cmd, t_token *token)
{
	if (cmd->input_fd != -1)
	{
		close(cmd->input_fd);
		cmd->input_fd = -1;
	}
	if (token->type == REDIR_IN)
		cmd->input_fd = open_infile(shell, token->next->value);
	else if (token->type == HEREDOC)
		cmd->input_fd = handle_heredoc(shell, token->next->value);
	if (cmd->input_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	resolve_output_fd(t_mini *shell, t_cmd *cmd, t_token *token)
{
	if (cmd->output_fd != -1)
	{
		close(cmd->output_fd);
		cmd->output_fd = -1;
	}
	if (token->type == REDIR_OUT)
		cmd->output_fd = open_outfile(shell, token->next->value);
	else if (token->type == REDIR_APPEND)
		cmd->output_fd = open_append_file(shell, token->next->value);
	if (cmd->output_fd == -2)
		return (FALSE);
	return (TRUE);
}

int	process_redir(t_mini *shell, t_cmd *cmd)
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
