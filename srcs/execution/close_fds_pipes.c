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
void	close_extra_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

/**
 * close_unused_fds - Closes unused file descriptors during pipeline execution.
 *
 * @shell: Pointer to the shell structure.
 * @i: Index of the current command in the pipeline.
 *
 * Ensures that unused pipe file descriptors are closed to avoid resource leaks. 
 * For a given command, closes the read end of the pipe for the current 
 * process and any remaining pipes beyond the current process in the pipeline.
 *
 * - Closes the read end of the pipe for the current process if applicable.
 * - Iterates over all remaining pipes in the pipeline and closes both their 
 *   read and write ends.
 */
void	close_unused_fds(t_mini *shell, int i)
{
	int	j;

	j = i + 1;
	if (shell->cmd_count >= 2 && i < shell->cmd_count - 1)
		close(shell->pipes[i][0]);
	while (j < shell->cmd_count - 1)
	{
		if (shell->pipes[j])
		{
			close(shell->pipes[j][0]);
			close(shell->pipes[j][1]);
		}
		j++;
	}
}

/**
 * close_fds_and_pipes - Closes all pipes.
 *
 * @shell: Pointer to the shell structure containing pipe array.
 *
 * Closes read and write ends of all pipes.
 */
void	close_all_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

/**
 * close_fds_and_pipes - Closes file descriptors and pipes for a command.
 *
 * @shell: Pointer to the shell structure containing pipe array.
 * @i: The index of the current command in the pipeline.
 *
 * Closes write ends of the pipe for the first command, read and write ends
 * for middle commands, and read ends for the last command.
 */
void	close_fds_and_pipes(t_mini *shell, int i)
{
	if (shell->cmd_count > 1)
	{
		if (i == 0)
			close(shell->pipes[i][1]);
		else if (i < shell->cmd_count - 1)
		{
			close(shell->pipes[i - 1][0]);
			close(shell->pipes[i][1]);
		}
		else if (i == shell->cmd_count - 1)
			close(shell->pipes[i - 1][0]);
	}
}
