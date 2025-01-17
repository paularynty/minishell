#include "minishell.h"

void	remove_eq(t_mini *shell, char *arg)
{
	char	*ptr;

	ptr = env_get_variable(shell->env, arg);
	if (!ptr)
		return ;
	*(ptr - 1) = '\0';
}

int	env_set_cwd(t_mini *shell)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (FALSE);
	if (!env_set_variable(shell, "PWD", dir))
	{
		free(dir);
		return (FALSE);
	}
	shell->cwd = dir;
	return (TRUE);
}

int	env_find_index(char **env, char *key)
{
	int		i;
	char	*index;

	i = 0;
	index = env_get_variable(env, key);
	if (index)
		index = index - ft_strlen(key) - 1;
	while (env[i])
	{
		if (index && env[i] == index)
			return (i);
		else if (!index && env[i][0] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

int	env_update_shlvl(t_mini *shell)
{
	char	*shlvl;
	long	temp;

	shlvl = env_get_variable(shell->env, "SHLVL");
	if (!shlvl)
		return (FALSE);
	temp = ft_atol(shlvl) + 1;
	if (temp >= 1000 || temp < 0)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(temp, STDERR_FILENO);
		ft_putstr_fd(") too high/low, resetting to 1\n", STDERR_FILENO);
		temp = 1;
	}
	shlvl = ft_itoa(temp);
	if (!shlvl)
		return (FALSE);
	if (!env_set_variable(shell, "SHLVL", shlvl))
	{
		free(shlvl);
		return (FALSE);
	}
	free(shlvl);
	return (TRUE);
}

char	**clone_env(char **env)
{
	int		i;
	char	**clone;

	i = 0;
	while (env && env[i])
		i++;
	clone = ft_calloc(1, (sizeof(char *) * (i + 1)));
	if (!clone)
		return (NULL);
	i = 0;
	while (env && env[i])
	{
		clone[i] = ft_strdup(env[i]);
		if (!clone[i])
		{
			ft_free_array(&clone);
			return (NULL);
		}
		i++;
	}
	return (clone);
}
