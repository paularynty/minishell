#include "minishell.h"

//in cd, if you use getcwd, it takes in absolute or relative path
//you can give the path to getcwd
//if path exists, you can move to it with chdir
//getcwd you can use for pwd

//1. with empty cd you go to home
//2. "cd -" goes to OLDPWD
//3. with path, you go to the cmd path

int	update_pwd(t_mini *shell)
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
	char	*old_pwd;
	char	*new_pwd;
	char	cwd[4096]; //PATH_MAX, doesn't work for me for some reason so hardcoding it
	
	old_pwd = getcwd(shell->cwd, sizeof(cwd));
	new_pwd = env_get_variable(shell->env, "OLDPWD");
	if (!old_pwd)
	{
		error_builtin(CD, NULL, "OLDPWD not set");
		return (FALSE);
	}
	printf("%s\n", new_pwd);
	if (!change_dir(new_pwd))
		return (FALSE);
	if (!env_set_variable(shell, "OLDPWD", old_pwd))
		return (FALSE);
	return (TRUE);
}

static int	cd_home(t_mini *shell)
{
	char	*home;
	char	*old_pwd;
	char	*cwd[4096];

	home = env_get_variable(shell->env, "HOME");
	if (!home)
	{
		error_builtin(CD, NULL, "HOME not set");
		return (FALSE);
	}
	old_pwd = getcwd(shell->cwd, sizeof(cwd));
	if (!old_pwd)
	{
		ft_putstr_fd("Getcwd for oldpwd failed\n", 2);
		return (FALSE);
	}
	return (change_dir(home));
}

int	builtin_cd(t_mini *shell)
{
	if (shell->cmd[2])
	{
		error_builtin(CD, NULL, "too many arguments");
		return (1);
	}
	if (!shell->cmd[1]) // if just "cd"
	{
		if (!cd_home(shell))
			return (1);
	}
	else if (ft_strncmp(shell->cmd[1], "-\0", 2) == 0)  // if "cd -"
	{
		if (!cd_oldpwd(shell))
			return (1);
	}
	else if (!change_dir(shell->cmd[1])) // if it's anything else other than cd or cd -
			return (1);
	if (!update_pwd(shell)) // update env for PWD, OLDPWD
		return (1);
	return (0);
}
