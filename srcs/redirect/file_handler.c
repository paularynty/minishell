#include "minishell.h"

// Tries to open input file and prints correct error in case of failure
int	open_infile(t_mini *shell, char *infile)
{
	int	input_fd;

	debug_print("Opening %s\n", infile);
	input_fd = open(infile, O_RDONLY);
	if (input_fd == -1)
	{
		if (access(infile, F_OK) == -1)
		{
			error_file(shell, infile, "No such file or directory", 1);
			return (-2);
		}
		if (access(infile, R_OK) == -1)
		{
			ft_putstr_fd(infile, 2);
			error_file(shell, infile, "Permission denied", 126);
			return (-2);
		}
	}
	return (input_fd);
}

// Tries to open output file and prints correct error in case of failure
int	open_outfile(t_mini *shell, char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, __O_DIRECTORY);
	if (fd_out != -1)
	{
		close(fd_out);
		error_file(shell, outfile, "Is a directory", 1);
		return (-2);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		error_file(shell, outfile, "Permission denied", 1);
		return (-2);
	}
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		error_file(shell, outfile, "No such file or directory", 1);
		return (-2);
	}
	return (fd_out);
}

/*Attempts to open output append file. 
Returns fd_out on success, -2 on failure with corresponding error message.*/
int	open_append_file(t_mini *shell, char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, O_DIRECTORY);
	if (fd_out != -1)
	{
		close(fd_out);
		error_file(shell, outfile, "Is a directory", 1);
		return (-2);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		error_file(shell, outfile, "Permission denied", 1);
		return (-2);
	}
	fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		error_file(shell, outfile, "No such file or directory", 1);
		return (-2);
	}
	return (fd_out);
}

void	heredoc_eof(int	line, char *delimiter)
{
	char	*line_str;

	line_str = ft_itoa(line);
	// if (!line_str)
	//	what do we do ?? 
	ft_putstr_fd("warning: here-document at line ", STDERR_FILENO);
	ft_putstr_fd(line_str, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	free(line_str);
}

/* handles heredoc by writing STDIN into a pipe until delimeter is met, then return pipe read end. 
	No actual files are created. */
int handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe failed");
		return (-2);
	}
	write(STDOUT_FILENO, "> ", 2);
	while (1) // Keep looping until we get the delimiter or EOF
	{
		line = get_next_line(STDIN_FILENO);  // Get a line from stdin
		if (line == NULL) // EOF encountered
		{
			heredoc_eof(__LINE__, delimiter);  // Handle EOF, need to make __LINE__ take line from terminal
        	break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 &&
		line[ft_strlen(delimiter)] == '\n')
        {
			free(line);
			break;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);  // Free the line after writing it to the pipe
		write(STDOUT_FILENO, "> ", 2);  // Prompt for the next line
	}
	close(pipe_fd[1]); // Close the write end of the pipe
	return (pipe_fd[0]); // Return the read end of the pipe
}
