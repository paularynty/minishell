/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:24 by prynty            #+#    #+#             */
/*   Updated: 2024/11/25 11:10:13 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//remember that getcwd is a big help
//in cd, if you use getcwd, it takes in absolute or relative path
//you can give the path to getcwd
//if path exists, you can move to it with chdir
//getcwd you can use for pwd

//1. with empty cd you go to home
//2. "cd -" goes to OLDPWD
//3. with path, you go to the cmd path

void	error_builtin(char *builtin, char *str, char *error_str)
{
	char	buffer[1024];

	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, builtin, sizeof(buffer) - 1);
	ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
	ft_strlcat(buffer, str, sizeof(buffer) - 1);
	if (!error_str)
		error_str = strerror(errno);
	if (error_str && error_str[0] != '\0')
	{
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
		ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	}
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}

static int	update_pwd(t_mini *shell)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (FALSE);
	free(shell->cwd);
	shell->cwd = dir;
	return (TRUE);
}

static int	change_dir(char *dir)
{
	if (chdir(dir) == -1)
	{
		error_builtin(CD, dir, NULL);
		return (FALSE);
	}
	return (TRUE);
}

static int	cd_oldpwd(t_mini *shell)
{
	return (TRUE);
}

static int	cd_home(t_mini *shell)
{
	char	*home;
	char	*old_pwd;

	home = get_env_var(shell->env, "HOME");
	if (!home)
	{
		error_builtin(CD, NULL, "HOME not set");
		return (FALSE);
	}
	old_pwd = getcwd(shell->cwd, sizeof(shell->cwd));
	if (!old_pwd)
	{
		ft_putstr_fd("Getcwd for oldpwd failed\n", 2);
		return (FALSE);
	}
	return (change_dir(home));
}

int	builtin_cd(t_mini *shell, char *line)
{
	char 	**cmd;
	char	*old_pwd;

	cmd = ft_split(line, ' ');
	if (!cmd)
	{
		free(cmd);
		return (FALSE);
	}
	// printf("%s %s %s %s\n", cmd[0], cmd[1], cmd[2], cmd[3]);
	// if (cmd[2])
	// {
	// 	error_builtin(CD, NULL, "too many arguments");
	// 	return (FALSE);
	// }
	if (!cmd[1])  // if just "cd"
	{
		if (!cd_home(shell))
			return (FALSE);
	}
	if (ft_strncmp(cmd[1], "-", 1) == 0)  // if "cd -"
	{
		old_pwd = get_env_var(shell->env, "OLDPWD");
		if (!old_pwd)
		{
			error_builtin(CD, NULL, "OLDPWD not set");
			return (FALSE);
		}
		if (!change_dir(old_pwd))
			return (FALSE);
	}
	if (!change_dir(cmd[1]))
		return (FALSE);
	if (!update_pwd(shell))
		return (FALSE);  // update env for PWD, OLDPWD
	return (TRUE);
}
