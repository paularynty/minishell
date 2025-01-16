#include "minishell.h"

/**
 * heredoc_eof - Handles the EOF condition during a here-document.
 *
 * @shell: Pointer to the shell structure.
 * @line: Line number where the EOF occurred.
 * @lim: Pointer to the lim string expected for the here-document.
 *
 * Generates and prints a warning message to `STDERR_FILENO` indicating that
 * a here-document was terminated by an unexpected EOF instead of the
 * specified lim. The message includes the line number and the expected
 * lim. If memory allocation fails, sets `shell->abort` to 1 and returns
 * FALSE.
 *
 * Returns TRUE on success or FALSE if memory allocation fails.
 */
static int	heredoc_eof(t_mini *shell, int line, char *lim)
{
	char	*line_str;
	char	buffer[1024];

	line_str = ft_itoa(line);
	if (!line_str)
	{
		perror("malloc");
		shell->abort = 1;
		return (FALSE);
	}
	ft_strlcpy(buffer, "minishell: warning: here-document at line ",
		sizeof(buffer) - 1);
	ft_strlcat(buffer, line_str, sizeof(buffer) - 1);
	ft_strlcat(buffer, " delimited by end-of-file (wanted `",
		sizeof(buffer) - 1);
	ft_strlcat(buffer, lim, sizeof(buffer) - 1);
	ft_strlcat(buffer, "')\n", sizeof(buffer) - 1);
	ft_putstr_fd(buffer, STDERR_FILENO);
	free(line_str);
	return (TRUE);
}

int	resolve_heredoc(t_mini *shell, t_cmd *cmd)
{
	t_token	*token;
	int		i;

	token = cmd->tokens;
	i = 0;
	while (token)
	{
		if (token->type == HEREDOC)
		{
			if (cmd->input_fd != -1)
			{
				close(cmd->input_fd);
				cmd->input_fd = -1;
			}
			cmd->input_fd = handle_heredoc(shell, token->next->value);
			if (cmd->input_fd == -1)
				return (FALSE);
			cmd->heredoc_i = i;
		}
		token = token->next;
		i++;
	}
	return (TRUE);
}

// static int	empty(void)
// {
// 	return (0);
// }

// static void	heredoc_loop(t_mini *shell, char *line, char *lim, int *pipe_fd)
// {
// 	rl_done = 0;
// 	rl_event_hook = empty;
// 	while (TRUE)
// 	{
// 		line = readline("> ");
// 		if (line == NULL)
// 		{
// 			heredoc_eof(shell, __LINE__, lim);
// 			break ;
// 		}
// 		// else if (rl_done == 1)
// 		// 	break ;
// 		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0
// 			&& line[ft_strlen(lim)] == '\0')
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(pipe_fd[1], line, ft_strlen(line));
// 		write(pipe_fd[1], "\n", 1);
// 		rl_clear_history();
// 		free(line);
// 	}
// }
static void    heredoc_loop(t_mini *shell, char *line, char *lim, int *pipe_fd)
{
	write(STDOUT_FILENO, "> ", 2);
    while (TRUE)
    {
        sig_heredoc(&sig_handler_heredoc);
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
        {
            heredoc_eof(shell, __LINE__, lim);
            break ;
        }
        if (ft_strncmp(line, lim, ft_strlen(lim)) == 0
            && line[ft_strlen(lim)] == '\n')
        {
            free(line);
            break ;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        free(line);
		write(STDOUT_FILENO, "> ", 2);
    }
}

/**
 * Writes input from STDIN into a pipe until a delimiter is encountered.
 *
 * @shell: Pointer to the shell structure.
 * @lim: String marking the end of the heredoc input.
 *
 * If heredoc (<<) symbol is encountered at call site, creates a pipe 
 * and prompts the user for input, writing each line into the pipe until
 * the specified delimiter is entered or EOF is reached, closes pipe write
 * end and returns pipe read end for further use.
 * 
 * Returns pipe read end on success, -2 on failure.
 **/
int	handle_heredoc(t_mini *shell, char *lim)
{
	int		pipe_fd[2];
	char	*line;

	line = NULL;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (FALSE);
	}
	sig_heredoc(&sig_handler_heredoc);
	heredoc_loop(shell, line, lim, pipe_fd);
	sig_reset();
	sig_init(&sig_handler_sigint);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

