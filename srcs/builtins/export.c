/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:45 by prynty            #+#    #+#             */
/*   Updated: 2024/11/28 10:44:34 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//if just export, you add to pending list, which is different from env
//you can export multiple vars in a single command

static void	sort_export_table(char **env)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*temp;

	i = 0;
	size = count_array_elements(env);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	builtin_export(t_mini *shell)
{
	char	*equal_char;
	char	**temp;
	int		i;

	i = 0;
	temp = env_clone(shell->env);
	if (!temp)
		return (FALSE);
	sort_export_table(temp);
	while (temp[i])
	{
		if (temp[i][0] != '\0')
		{
			printf("declare -x ");
			equal_char = ft_strchr(temp[i], '=');
			if (equal_char)
				printf("%s\"%s\"\n", temp[i], equal_char + 1);
			else
				printf("%s\n", temp[i]);
		}
		i++;
	}
	ft_free_array(&temp);
	return (TRUE);
}
