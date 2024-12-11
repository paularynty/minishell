/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:39 by prynty            #+#    #+#             */
/*   Updated: 2024/11/28 10:42:33 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TO DO: 
//exit with more than one arg should print "minishell: exit: too many arguments"
//and exit code should be 1
//if exited with non-numeric argument, should print "minishell: exit: [str] numeric argument required"
//and exit code should be 2

void	builtin_exit(t_mini *shell, char **cmd)
{
	int	i;
	int	numeric_flag;
	int	extra_args;

	i = 0;
	numeric_flag = FALSE;
	extra_args = FALSE;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (count_array_elements(cmd) > 2)
		extra_args = TRUE;
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (!ft_isdigit(cmd[1][i]))
				numeric_flag = TRUE;
			i++;
		}
		shell->exit_code = ft_atoi(cmd[1]);
	}
	if (extra_args)
	{
		error_builtin(EXIT, NULL, "too many arguments");
		shell->exit_code = 1;
	}
	else if (numeric_flag)
	{
		error_builtin(EXIT, cmd[1], "numeric argument required");
		shell->exit_code = 2;
	}
	exit(shell->exit_code);
}
