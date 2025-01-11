#include "minishell.h"

/**
 * Closes a file descriptor if it is not a standard one.
 *
 * @fd: The file descriptor to be closed.
 *
 * Checks if the given file descriptor is greater than 2 (i.e., not 
 * `STDIN_FILENO`, `STDOUT_FILENO`, or `STDERR_FILENO`). 
 * If so, it closes the file descriptor to release resources.
 * 
 */
static void	close_extra_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

/**
 * redirect_fd - Redirects a file descriptor to another.
 *
 * @src_fd: The source file descriptor to be redirected.
 * @dest_fd: The destination file descriptor to redirect to.
 *
 * If the source file descriptor (`src_fd`) is not the same as the 
 * destination (`dest_fd`), performs the redirection using `dup2()`. If 
 * `dup2()` fails, logs an error using `perror`, closes the source file 
 * descriptor, and returns `FALSE`. If the redirection succeeds, the source 
 * file descriptor is closed.
 *
 * Returns TRUE on success, or FALSE on failure.
 */
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

/**
 * resolve_input - Resolves the input file descriptor for a command.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @token: Pointer to the token specifying the redirection.
 *
 * Resolves input redirections based on the type of the token. For `REDIR_IN`, 
 * opens the file specified in the token's next value using `open_infile()`. 
 * For `HEREDOC`, processes the heredoc using `handle_heredoc()`. 
 * If an input file descriptor is already open, it is closed before opening a 
 * new one. If an error occurs (e.g., invalid file), returns `FALSE`.
 *
 * Returns TRUE on success, or FALSE on failure.
 */
int	resolve_input(t_mini *shell, t_cmd *cmd, t_token *token)
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

/**
 * resolve_output - Resolves the output file descriptor for a command.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 * @token: Pointer to the token specifying the redirection.
 *
 * Resolves output redirections based on the type of the token. For `REDIR_OUT`, 
 * opens the file specified in the token's next value using `open_outfile()`. 
 * For `REDIR_APPEND`, opens the file in append mode using `open_append_file()`. 
 * If an output file descriptor is already open, it is closed before opening a 
 * new one. If an error occurs (e.g., invalid file), returns `FALSE`.
 *
 * Returns TRUE on success, or FALSE on failure.
 */
int	resolve_output(t_mini *shell, t_cmd *cmd, t_token *token)
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

/**
 * handle_redirection - Handles input and output redirections for a command.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Iterates through cmd->tokens to process redirections. 
 * For input redirections (e.g., `REDIR_IN`, `HEREDOC`), calls 
 * `resolve_input()` to resolve the input file descriptor. 
 * For output redirections (e.g., `REDIR_OUT`, `REDIR_APPEND`), 
 * calls `resolve_output()` to resolve the output file descriptor. 
 * If a redirection fails, closes the other file descriptor if needed 
 * and returns `FALSE`.
 *
 * Returns TRUE if all redirections are processed successfully, 
 * or FALSE if any redirection fails.
 */
int	handle_redirection(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
		{
			if (!resolve_input(shell, cmd, token))
			{
				close_extra_fd(cmd->output_fd);
				return (FALSE);
			}
		}
		else if (token->type == REDIR_OUT || token->type == REDIR_APPEND)
		{
			if (!resolve_output(shell, cmd, token))
			{
				close_extra_fd(cmd->input_fd);
				return (FALSE);
			}
		}
		token = token->next;
	}
	return (TRUE);
}
