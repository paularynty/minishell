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

/* Opens heredoc. */
int	open_heredoc(t_mini *shell, char *heredoc_file)
{
	int	input_fd;

	input_fd = open(heredoc_file, O_RDONLY);
	if (input_fd == -1)
	{
		if (access(heredoc_file, F_OK) == -1)
		{
			error_file(shell, heredoc_file, "No such file or directory", 1);
			return (-2);
		}
		if (access(heredoc_file, R_OK) == -1)
		{
			error_file(shell, heredoc_file, "Permission denied", 1);
			return (-2);
		}
	}
	return (input_fd);
}
