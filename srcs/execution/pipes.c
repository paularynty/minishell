#include "minishell.h"

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

/*	Closes unused pipes.*/
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

/* Creates pipes from shell->pipes array. All pipes are created at the same time. */
int	create_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		if (pipe(shell->pipes[i]) == -1)
		{
			perror("pipe failed");
			return (FALSE); // call close open fd's in calling process_commands
		}
		i++;
	}
	return (TRUE);
}

/* Allocates memory for 2D pipe array (int **pipes).*/
static int	allocate_pipes(t_mini *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!shell->pipes)
		return (FALSE);
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipes[i] = ft_calloc(2, sizeof(int)); //2 for fd[0] and fd[1] for each pipe array element
		if (!shell->pipes[i])
		{
			free_pipes(shell, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/* Creates and allocates PID array (one PID for each shell->cmd_count).*/
static int	allocate_pids(t_mini *shell)
{
	shell->pids = ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		// free and close everything and exit minishell (malloc failure);
		return (FALSE);
	}
	return (TRUE);
}


/*Calls allocate_pids.
Calls allocate_pipes() and create_pipes() if cmd_count > 1.
Returns to exec_child().*/
int	init_pipeline(t_mini *shell)
{
	if (!allocate_pids(shell))
		return (FALSE);
	if (shell->cmd_count > 1)
	{
		if (!allocate_pipes(shell))
			return (FALSE);
		if (!create_pipes(shell))
		{
			free(shell->pids);
			// close all open fds, free everything, and determine exit code
			return (FALSE);
		}
		// debug_print("cmd count: %d\n", shell->cmd_count);
		// debug_print("pipe read end: %d\n", shell->pipes[0][0]);
		// debug_print("pipe write end: %d\n", shell->pipes[0][1]);
	}
	return (TRUE);
}
