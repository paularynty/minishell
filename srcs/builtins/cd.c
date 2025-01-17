#include "minishell.h"

/**
 * update_pwd - Updates the current working directory in the shell structure.
 *
 * @shell: Pointer to the shell structure.
 *
 * Retrieves the current working directory using `getcwd()` and updates the 
 * `shell->cwd` field to reflect the new directory. Frees the memory of the 
 * previous `cwd` value before assigning the updated value. If `getcwd()` 
 * fails, the function returns FALSE.
 *
 * Returns TRUE on success or FALSE if `getcwd()` fails.
 */
int	update_pwd(t_mini *shell)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{	
		error_builtin(CD, NULL, "getcwd: cannot access parent directories:\
		No such file or directory");
		chdir("..");
		return (FALSE);
	}
	free(shell->cwd);
	shell->cwd = dir;
	if (!env_set_variable(shell, "PWD", shell->cwd))
		return (FALSE);
	return (TRUE);
}

/**
 * change_dir - Changes the current working directory.
 *
 * @dir: Path to the target directory.
 *
 * Uses the `chdir()` system call to change the current working directory 
 * to the specified `dir`. If the operation fails, an error message is 
 * displayed using the `error_builtin()` function.
 *
 * Returns TRUE on success or FALSE if `chdir()` fails.
 */
static int	change_dir(char *dir)
{
	if (chdir(dir) == -1)
	{
		error_builtin(CD, dir, NULL);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * cd_oldpwd - Changes the working directory to the previous working directory.
 *
 * @shell: Pointer to the shell structure.
 *
 * Retrieves the previous working directory (`OLDPWD`) from the shell's 
 * environment variables and changes to it using `change_dir()`. If successful, 
 * updates the `OLDPWD` environment variable to the current working directory.
 *
 * - Prints the new directory path to stdout.
 * - Handles errors if `OLDPWD` is not set, or if any operation fails.
 *
 * Returns TRUE on success or FALSE on failure.
 */
static int	cd_oldpwd(t_mini *shell)
{
	char	*old_pwd;
	char	*new_pwd;
	char	cwd[4096];

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

/**
 * cd_home - Changes the working directory to the user's home directory.
 *
 * @shell: Pointer to the shell structure.
 *
 * Retrieves the `HOME` environment variable and changes to the corresponding 
 * directory using `change_dir()`. If successful, updates the `OLDPWD` 
 * environment variable to the current working directory. Handles errors if 
 * `HOME` is not set or if any operation fails.
 *
 * Returns TRUE on success or FALSE on failure.
 */
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
		return (FALSE);
	return (change_dir(home));
}

int	builtin_cd(t_mini *shell, char **args)
{
	if (count_array_elements(args) > 2)
	{
		error_builtin(CD, NULL, "too many arguments");
		return (1);
	}
	if (!args[1])
	{
		if (!cd_home(shell))
			return (1);
	}
	else if (ft_strncmp(args[1], "-\0", 2) == 0)
	{
		if (!cd_oldpwd(shell))
			return (1);
	}
	else if (!change_dir(args[1]))
		return (1);
	if (!update_pwd(shell))
		return (1);
	return (0);
}

// static int	cd_choices(t_mini *shell, char *cwd, char **args)
// {
// 	if (!args[1])
// 	{
// 		if (!cd_home(shell))
// 			return (FALSE);
// 		return (TRUE);
// 	}
// 	else if (ft_strncmp(args[1], "-\0", 2) == 0)
// 	{
// 		if (!cd_oldpwd(shell))
// 			return (FALSE);
// 		return (TRUE);
// 	}
// 	else if (!change_dir(args[1]))
// 		return (FALSE);
// 	shell->cwd = cwd;
// 	return (TRUE);
// }

// static int	no_cwd(t_mini *shell, char **cwd)
// {
// 	char	*pwd;

// 	pwd = env_get_variable(shell->env, "PWD");
// 	if (!pwd)
// 	{
// 		*cwd = ft_strdup(pwd);
// 		if (!(*cwd))
// 		{
// 			perror("malloc");
// 			return (FALSE);
// 		}
// 	}
// 	else
// 	{
// 	error_builtin(CD, NULL, "getcwd: cannot access parent directories:
//No such file or directory");
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }

/**
 * builtin_cd - Built-in `cd` command for the shell.
 *
 * @shell: Pointer to the shell structure.
 * @cmd: Pointer to the command structure.
 *
 * Handles directory changes based on the arguments provided:
 * - If no argument is provided, changes to the home directory (`cd_home()`).
 * - If the argument is `-`, changes to the previous directory (`cd_oldpwd()`).
 * - Otherwise, attempts to change to the specified directory.
 * 
 * Validates the arguments to ensure only one argument is provided. Handles 
 * errors for invalid input, missing environment variables, or directory 
 * change failures. Updates the current working directory (`update_pwd()`) 
 * after a successful change.
 *
 * Returns 0 on success or 1 on failure.
 */
// int	builtin_cd(t_mini *shell, char **args)
// {
// 	char	*cwd;

// 	if (count_array_elements(args) > 2)
// 	{
// 		error_builtin(CD, NULL, "too many arguments");
// 		return (1);
// 	}
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		if (!no_cwd(shell, &cwd))
// 			return (1);
// 	}
// 	if (!cd_choices(shell, cwd, args))
// 	{
// 		free(cwd);
// 		return (1);
// 	}
// 	printf("%s\n", cwd);
// 	if (!env_set_variable(shell, "PWD", cwd))
// 		return (FALSE);
// 	return (0);
// }
