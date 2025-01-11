#include "minishell.h"

/*	Frees PID array. */
// void	free_pids(pid_t *pids)
// {
// 	size_t	i;

// 	i = 0;
// 	while (pids[i])
// 	{
// 		free(pids[i]);
// 		i++;
// 	}
// 	free(pids);
// 	pids = NULL; //not sure if needed but adding this as muscle memory lmao
// }

/**
 * wait_for_children - Waits for all child processes to terminate.
 *
 * @shell: Pointer to the shell structure.
 *
 * Loops over all child process IDs stored in `shell->pids` and waits for 
 * each process to terminate using `waitpid()`. Updates the shell's 
 * `exit_code` based on the exit status or termination signal of each 
 * process:
 * - If a child exits normally, the exit status is assigned to 
 *   `shell->exit_code`.
 * - If a child is terminated by a signal, assigns a signal-based 
 *   exit code (e.g., `130` for SIGINT).
 *
 * On `waitpid()` failure, assigns `errno` to `shell->exit_code` and prints 
 * an error message.
 *
 * Returns the final `shell->exit_code` after waiting for all children.
 */
int	wait_for_children(t_mini *shell)
{
	int		i;
	int		status;
	int		signum;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			shell->exit_code = errno;
		}
		if (WIFEXITED(status))
		{
			if (g_mrworldwide == 1)
				// g_mrworldwide = 1;
				shell->exit_code = 1;
			else
				// g_mrworldwide = WEXITSTATUS(status); //or shell->exit_code?
				shell->exit_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			signum = WTERMSIG(status);
			if (signum == SIGINT)
				// g_mrworldwide = 130;
				shell->exit_code = 130;
		}
		i++;
	}
	return (shell->exit_code);
}

/**
 * is_dir - Checks if a given path is a directory.
 *
 * @path: The file path to check.
 *
 * Uses `stat()` to retrieve the file status for the given path and checks 
 * if the file mode indicates a directory using `S_ISDIR()`. Returns 
 * `false` if the `stat()` call fails.
 *
 * Returns `true` if the path is a directory, or `false` otherwise.
 */
bool	is_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (false);
	return (S_ISDIR(sb.st_mode));
}

/**
 * check_access - Validates access permissions for a command.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Command path to validate.
 *
 * Performs a series of checks on the given command to determine its 
 * accessibility and validity. Upon encountering any error, calls
 * `error_cmd()` with the corresponding error message and exit code.
 * */
void	check_access(t_mini *shell, t_cmd *cmds, char *cmd) // here cmds is starting from head
{
	if (!cmd)
		error_cmd(shell, cmds, cmd, "command not found", 127);
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			error_cmd(shell, cmds, cmd, "No such file or directory", 1);
		else
			error_cmd(shell, cmds, cmd, "command not found", 127);
	}
	if (is_dir(cmd) == true)
	{
		if (ft_strchr(cmd, '/'))
			error_cmd(shell, cmds, cmd, "Is a directory", 126);
		else
			error_cmd(shell, cmds, cmd, "command not found", 127);
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			error_cmd(shell, cmds, cmd, "Permission denied", 126);
		else
			error_cmd(shell, cmds, cmd, "command not found", 127);
	}
}
