#include "minishell.h"

static int	update_pwd(t_mini *shell, char *pwd)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{	
		free(dir);
		return (FALSE);
	}
	free(shell->cwd);
	shell->cwd = dir;
	if (!env_set_variable(shell, "OLDPWD", pwd))
		return (FALSE);
	if (!env_set_variable(shell, "PWD", shell->cwd))
		return (FALSE);
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
	char	*new_pwd;

	new_pwd = env_get_variable(shell->env, "OLDPWD");
	if (!new_pwd)
	{
		error_builtin(CD, NULL, "OLDPWD not set");
		return (FALSE);
	}
	printf("%s\n", new_pwd);
	if (!change_dir(new_pwd))
		return (FALSE);
	return (TRUE);
}

static int	cd_home(t_mini *shell)
{
	char	*home;

	home = env_get_variable(shell->env, "HOME");
	if (!home)
	{
		error_builtin(CD, NULL, "HOME not set");
		return (FALSE);
	}
	if (!change_dir(home))
		return (FALSE);
	return (TRUE);
}

int	builtin_cd(t_mini *shell, char **args)
{
	char	*pwd;

	if (count_array_elements(args) > 2)
	{
		error_builtin(CD, NULL, "too many arguments");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (args[1] == NULL)
	{
		if (!cd_home(shell))
			return (free(pwd), 1);
	}
	else if (ft_strncmp(args[1], "-\0", 2) == 0)
	{
		if (!cd_oldpwd(shell))
			return (free(pwd), 1);
	}
	else if (!change_dir(args[1]))
		return (free(pwd), 1);
	if (!update_pwd(shell, pwd))
		return (free(pwd), 1);
	free(pwd);
	return (0);
}
