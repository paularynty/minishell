/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:34 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 16:00:38 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_update_shell_level(t_mini *shell)
{
	char	*shell_level;
	int		new_level;

	shell_level = env_get_variable(shell->env, "SHLVL");
	new_level = ft_atoi(shell_level) + 1;
	if (new_level >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(new_level, STDERR_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
		new_level = 1;
	}
	shell_level = ft_itoa(new_level);
	if (!shell_level)
		return (FALSE);
	if (!env_set_variable("SHLVL", shell_level))
	{
		free(shell_level);
		return (FALSE);
	}
	free(shell_level);
	return (TRUE);
}

//env takes in no args, only prints the env list
//when running env -i ./minishell and env as command
//env list should only be PWD, SHLVL and _=/usr/bin/env
int	builtin_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
