/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:34 by prynty            #+#    #+#             */
/*   Updated: 2024/11/18 16:20:14 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
