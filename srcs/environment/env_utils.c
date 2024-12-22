#include "minishell.h"
char	*env_get_variable(char **env, char *key)
{
	int		i;
	size_t	key_len;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && *(env[i] + key_len) == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

static int	env_add_variable(t_mini *shell, char *variable)
{
	char	**new;
	int		i;

	i = 0;
	while (shell->env && shell->env[i])
		i++;
	new = ft_calloc(1, (i + 2) * sizeof(char *));
	if (!new)
		return (0);
	ft_memcpy(new, shell->env, i * sizeof(char *));
	new[i] = variable;
	free(shell->env);
	shell->env = new;
	return (1);
}

static int	env_find_index(char **env, char *key)
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

int	env_set_variable(t_mini *shell, char *key, char *value)
{
	char	*new;
	size_t	new_len;
	int		index;

	new_len = ft_strlen(key) + ft_strlen(value) + 2;
	new = ft_calloc(1, new_len);
	if (!new)
		return (FALSE);
	ft_strlcat(new, key, new_len);
	ft_strlcat(new, "=", new_len);
	ft_strlcat(new, value, new_len);
	index = env_find_index(shell->env, key);
	if (index == -1)
	{
		if (!env_add_variable(shell, new))
		{
			free(new);
			return (FALSE);
		}
		return (TRUE);
	}
	free(shell->env[index]);
	shell->env[index] = new;
	return (TRUE);
}

int	env_update_shlvl(t_mini *shell)
{
	char	*shlvl;
	int		temp;

	shlvl = env_get_variable(shell->env, "SHLVL");
	temp = ft_atoi(shlvl) + 1;
	if (temp >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(temp, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
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
			return (FALSE);
		}
		i++;
	}
	return (clone);
}
