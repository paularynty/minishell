/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:49:33 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 13:32:23 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_access(t_mini *shell, char *cmd, char **cmd_array)
{
	int	is_dir;

	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			errno = ENOENT;
		else
			errno = 0;
		error_cmd(shell, cmd, cmd_array);
	}
	is_dir = open(cmd, __O_DIRECTORY);
	if (is_dir >= 0)
	{
		close(is_dir);
		if (cmd[ft_strlen(cmd) - 1] == '/')
			errno = EISDIR;
		else
			errno = 0;
		error_cmd(shell, cmd, cmd_array);
	}
	if (access(cmd, X_OK) == -1)
	{	
		errno = EACCES;
		error_cmd(shell, cmd, cmd_array);
	}
}

static char	**get_env_path(char **env)
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

static char	*get_full_path(char **env_path, char *cmd)
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

static char	*get_cmd_path(t_mini *shell, char *cmd, char **cmd_array)
{
	char	*cmd_path;
	char	**env_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
		{
			errno = ENOENT;
			error_cmd(shell, cmd, cmd_array);
		}
	}
	env_path = get_env_path(shell->env);
	if (!env_path)
		return (NULL);
	cmd_path = get_full_path(env_path, cmd);
	ft_free_array(&env_path);
	return (cmd_path);
}

void	prep_command(t_mini *shell, char *line)
{
	shell->cmd = ft_split(line, ' ');
	if (!shell->cmd)
		ft_free_array(&shell->cmd);
	if (!shell->cmd || !shell->cmd[0])
		error_cmd(shell, shell->cmd[0], shell->cmd);
}

void	execute(t_mini *shell)
{
	char		*cmd_path;

	cmd_path = get_cmd_path(shell, shell->cmd[0], shell->cmd);
	if (!cmd_path)
		check_access(shell, shell->cmd[0], shell->cmd);
	check_access(shell, cmd_path, shell->cmd);
	execve(cmd_path, shell->cmd, shell->env);
	free(cmd_path);
	error_cmd(shell, shell->cmd[0], shell->cmd);
}
