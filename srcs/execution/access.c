#include "minishell.h"

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
 * access_exists - Checks if a command file exists.
 *
 * @shell: Pointer to the shell structure.
 * @head: Pointer to the command structure (if necessary for error handling).
 * @cmd: Command path to validate.
 *
 * This function checks if the given command file exists using the `access` 
 * function with the `F_OK` flag. If the file does not exist, it sets the 
 * appropriate error message and exit code. It differentiates between a file 
 * with a '/' character (indicating a file path) and other command names.
 */
static void	access_exists(t_mini *shell, t_cmd *head, char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			shell->exit_code = 1;
			error_cmd(shell, head, cmd, "No such file or directory");
		}
		else
		{
			shell->exit_code = 127;
			error_cmd(shell, head, cmd, "command not found");
		}
	}
}

/**
 * access_is_dir - Checks if a command path refers to a directory.
 *
 * @shell: Pointer to the shell structure.
 * @head: Pointer to the command structure (if necessary for error handling).
 * @cmd: Command path to validate.
 *
 * This function checks if the given command is a directory using the `is_dir` 
 * function. If the command path is determined to be a directory, it sets an 
 * error message and exit code. It also differentiates between a file with 
 * a '/' character (indicating a directory path) and a command name.
 */
static void	access_is_dir(t_mini *shell, t_cmd *head, char *cmd)
{
	if (is_dir(cmd) == true)
	{
		if (ft_strchr(cmd, '/'))
		{
			shell->exit_code = 126;
			error_cmd(shell, head, cmd, "Is a directory");
		}
		else
		{
			shell->exit_code = 127;
			error_cmd(shell, head, cmd, "command not found");
		}
	}
}

/**
 * access_is_executable - Checks if a command is executable.
 *
 * @shell: Pointer to the shell structure.
 * @head: Pointer to the command structure (if necessary for error handling).
 * @cmd: Command path to validate.
 *
 * This function checks if the command exists and if it has executable 
 * permissions using the `access` function with both `F_OK` and `X_OK` flags. 
 * If the command exists but is not executable, it sets an appropriate error 
 * message and exit code.
 */
static void	access_is_executable(t_mini *shell, t_cmd *head, char *cmd)
{
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
		{
			shell->exit_code = 126;
			error_cmd(shell, head, cmd, "Permission denied");
		}
		else
		{
			shell->exit_code = 127;
			error_cmd(shell, head, cmd, "command not found");
		}
	}
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
void	check_access(t_mini *shell, t_cmd *head, char *cmd)
{
	if (!cmd)
	{
		shell->exit_code = 127;
		error_cmd(shell, head, cmd, "command not found");
	}
	access_exists(shell, head, cmd);
	access_is_dir(shell, head, cmd);
	access_is_executable(shell, head, cmd);
}
