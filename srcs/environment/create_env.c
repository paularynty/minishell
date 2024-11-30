/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:36:33 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 16:26:40 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_get_variable(char **env, char *key)
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

int	env_set_variable(char *key, char *value)
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
	free(new);
	return (TRUE);
}

void	clean_env(t_env **env, void (*clear)(void *))
{
	t_env	*var;
	t_env	*temp;
	
	if (!env || !clear)
		return ;
	var = *env;
	while (var)
	{
		temp = var->next;
		clear(var->key);
		clear(var->value);
		free(var);
		var = temp;
	}
	*env = NULL;
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

// t_env	*clone_env(char **env)
// {
// 	char	**clone;
// 	t_env	*list;
// 	t_env	*new;
// 	char	*key;
// 	char	*value;

// 	list = NULL;
// 	while (*env)
// 	{
// 		key = ft_strdup(list->key);
// 		if (!key)
// 		{
// 			clean_env(&new, &free);
// 			return (NULL);
	
// 		}
// 		value = ft_strdup(list->value);
// 		if (!value)
// 		{
// 			clean_env(&list, &free);
// 			free(key);
// 			return (NULL);
// 		}
// 	}
// }

t_env	*create_env_list(char *key, char *value)
{
	t_env	*var;
	
	if (!key || !value)
		return (NULL);
	var = (t_env *)malloc(sizeof(t_env));
	if (!var)
		return (NULL);
	var->key = key;
	var->value = value;
	if (!value || *value == '\0')
		var->flag = FALSE;
	else
		var->flag = TRUE;
	var->next = NULL;
	return (var);
}
