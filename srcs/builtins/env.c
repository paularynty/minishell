/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:34 by prynty            #+#    #+#             */
/*   Updated: 2024/11/25 11:09:11 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_var(char **env, char *key)
{
	int		i;
	size_t	key_len;

	if (!env || !key)
		return (NULL);
	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && *(env[i] + key_len) == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	set_env_var(char *key, char *value)
{
	char	*new;
	size_t	new_len;

	new_len = ft_strlen(key) + ft_strlen(value) + 2;
	new = ft_calloc(1, new_len);
	if (!new)
		return (FALSE);
	ft_strlcat(new, key, new_len);
	ft_strlcat(new, "=", new_len);
	ft_strlcat(new, value, new_len);
	return (TRUE);
}

char	**env_clone(char **env)
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

//env takes in no args, only prints the env list
//when running env -i ./minishell and env as command
//env list should only be PWD, SHLVL and _=/usr/bin/env
void	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
}
