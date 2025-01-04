#include "minishell.h"

char	**get_env_path(char **env)
{
	char	**env_path;

	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	if (!*env)
	{
		errno = ENOENT;
		return (NULL);
	}
	env_path = ft_split(*env + 5, ':');
	if (!env_path)
		return (NULL);
	return (env_path);
}

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

char	*get_cmd_path(t_mini *shell, char *cmd)
{
	char	*cmd_path;
	char	**env_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
			error_cmd(shell, cmd, "No such file or directory", 127);
	}
	env_path = get_env_path(shell->env);
	if (!env_path)
		return (NULL);
	cmd_path = get_full_path(env_path, cmd);
	ft_free_array(&env_path);
	return (cmd_path);
}
