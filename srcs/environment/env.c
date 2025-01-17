#include "minishell.h"

static int	env_add_variable(t_mini *shell, char *variable)
{
	char	**new;
	int		i;

	i = 0;
	while (shell->env && shell->env[i])
		i++;
	new = ft_calloc(1, (i + 2) * sizeof(char *));
	if (!new)
		return (FALSE);
	ft_memcpy(new, shell->env, i * sizeof(char *));
	new[i] = variable;
	free(shell->env);
	shell->env = new;
	return (TRUE);
}

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

int	env_set_variable(t_mini *shell, char *key, char *value)
{
	char	*new;
	size_t	new_len;
	int		index;

	if (!key || !value)
		return (FALSE);
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
			return (free(new), FALSE);
		return (TRUE);
	}
	free(shell->env[index]);
	shell->env[index] = new;
	return (TRUE);
}

int	builtin_env(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env && shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
