#include "minishell.h"

/**
 * get_env_path - Retrieves the `PATH` environment variable as an array of paths.
 *
 * @env: Array of environment variables.
 *
 * Searches through the environment variable list to find the `PATH` variable. 
 * If found, splits its value into an array of directory paths using `ft_split()` 
 * and returns the array. If `PATH` is not found or memory allocation fails, 
 * returns `NULL` and sets `errno` to `ENOENT`.
 *
 * Returns a pointer to the array of paths, or NULL on failure.
 */
char	**get_env_path(char **env)
{
	char	**env_path;

	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (NULL);
	env_path = ft_split(*env + 5, ':');
	if (!env_path)
		return (NULL);
	return (env_path);
}

/**
 * get_full_path - Constructs the full path to a command.
 *
 * @env_path: Array of directories from the `PATH` environment variable.
 * @cmd: The command to locate.
 *
 * Iterates through the `env_path` directories, appending the command name to 
 * each directory to form a full path. Checks if the constructed path exists 
 * using `access()`. If a valid path is found, returns the full path. If no 
 * valid path is found, returns `NULL`. Frees intermediate memory allocations.
 *
 * Returns the full path to the command, or NULL if not found.
 */
char	*get_full_path(char **env_path, char *cmd)
{
	char	*temp_path;
	char	*full_path;

	while (*env_path)
	{
		temp_path = ft_strjoin(*env_path, "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		env_path++;
	}
	return (NULL);
}

/**
 * get_cmd_path - Resolves the executable path for a command.
 *
 * @shell: Pointer to the shell structure.
 * @cmds: Pointer to the command structure.
 * @cmd: The command to resolve.
 *
 * Checks if the command contains a `/`, and if so, verifies its existence 
 * using `access()`. If the command does not contain a `/`, retrieves the 
 * environment `PATH` using `get_env_path()` and searches for the command 
 * using `get_full_path()`. If the command is not found, logs an error using 
 * `error_cmd()`. Frees any allocated memory before returning the result.
 *
 * Returns the resolved command path, or NULL if the command cannot be found.
 */
char	*get_cmd_path(t_mini *shell, t_cmd *cmds, char *cmd)
{
	char	*cmd_path;
	char	**env_path;

	if (!cmd || *cmd == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
		{	
			shell->exit_code = 127;
			error_cmd(shell, cmds, cmd, "No such file or directory");
		}
	}
	env_path = get_env_path(shell->env);
	if (!env_path)
		return (NULL);
	cmd_path = get_full_path(env_path, cmd);
	ft_free_array(&env_path);
	return (cmd_path);
}
