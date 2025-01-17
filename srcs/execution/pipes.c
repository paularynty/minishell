#include "minishell.h"

/**
 * create_pipes - Creates all pipes required for a pipeline.
 *
 * @shell: Pointer to the shell structure.
 *
 * Iterates over the `shell->pipes` array and creates a pipe for each pair 
 * of commands in the pipeline. The number of pipes created is one less 
 * than the total number of commands (`cmd_count - 1`).
 *
 * - Allocates the required pipes using the `pipe()` system call.
 * - Prints an error message and returns FALSE if a pipe creation fails.
 *
 * Returns TRUE on success or FALSE on failure.
 */
int	create_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		if (pipe(shell->pipes[i]) == -1)
		{
			perror("minishell: pipe failed");
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/**
 * allocate_pipes - Allocates memory for the pipe array.
 *
 * @shell: Pointer to the shell structure.
 *
 * Allocates a 2D array of file descriptors for the pipes, where each pipe 
 * consists of two file descriptors: one for reading and one for writing. 
 * The number of pipes is `cmd_count - 1`. Ensures that any memory allocated 
 * for partially completed pipes is freed if an allocation fails.
 *
 * - Uses `ft_calloc` to allocate memory for each pipe.
 * - Frees already allocated pipes and returns FALSE on allocation failure.
 *
 * Returns TRUE on successful allocation or FALSE on failure.
 */
static int	allocate_pipes(t_mini *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!shell->pipes)
		return (FALSE);
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipes[i] = ft_calloc(2, sizeof(int));
		if (!shell->pipes[i])
		{
			free_pipes(shell, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/**
 * allocate_pids - Allocates memory for the PID array.
 *
 * @shell: Pointer to the shell structure.
 *
 * Allocates an array to store the process IDs (PIDs) for each command 
 * in the pipeline. The size of the array is equal to the number of commands 
 * (`cmd_count`).
 *
 * Returns TRUE on success or FALSE on memory allocation failure.
 */
static int	allocate_pids(t_mini *shell)
{
	shell->pids = ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		ft_putstr_fd("minishell: memory allocation failed\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * init_pipeline - Initializes the pipeline for command execution.
 *
 * @shell: Pointer to the shell structure.
 *
 * Prepares the necessary resources for executing commands in a pipeline:
 * - Allocates the PID array to store process IDs for each command.
 * - Allocates and creates pipes if there are multiple commands in the pipeline 
 *   (`cmd_count > 1`).
 *
 * Ensures proper error handling by freeing allocated resources and closing 
 * file descriptors in case of failure.
 *
 * - Calls `allocate_pids()` to allocate memory for the PID array.
 * - Calls `allocate_pipes()` to allocate the pipe array and `create_pipes()` 
 *   to initialize the pipes if required.
 *
 * Returns TRUE on successful initialization or FALSE on failure.
 */
int	init_pipeline(t_mini *shell)
{
	if (!allocate_pids(shell))
		return (FALSE);
	if (shell->cmd_count > 1)
	{
		if (!allocate_pipes(shell))
			return (FALSE);
		if (!create_pipes(shell))
			return (FALSE);
	}
	return (TRUE);
}
