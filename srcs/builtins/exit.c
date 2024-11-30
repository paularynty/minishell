/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:39 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 16:18:19 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// exit without args:
// prints “exit\n” with exit code 0
// exit [numeric arg], e.g. exit 5:
// prints "exit\n", exit code is numeric arg
// exit w/ >1 arg:
// “exit\n minishell: exit: too many arguments”, exit code 1
// exit w/ non numeric args: 
// “exit\n minishell: exit: [arg]: numeric argument required”, exit code 2

//TO DO:
//handle "-" and "+"
//does the shell actually exit when too many args???

int	builtin_exit(t_mini *shell)
{
	int	i;
	int	numeric_flag;
	int	extra_args;

	i = 0;
	numeric_flag = FALSE;
	extra_args = FALSE;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (count_array_elements(shell->cmd) > 2)
		extra_args = TRUE;
	if (shell->cmd[1])
	{
		while (shell->cmd[1][i])
		{
			if (!ft_isdigit(shell->cmd[1][i]))
				numeric_flag = TRUE;
			i++;
		}
		shell->exit_code = ft_atoi(shell->cmd[1]);
	}
	if (numeric_flag)
	{
		error_builtin(EXIT, shell->cmd[1], "numeric argument required");
		shell->exit_code = 2;
	}
	else if (extra_args)
	{
		error_builtin(EXIT, NULL, "too many arguments");
		shell->exit_code = 1;
	}
	shell->exit_flag = TRUE;
	return (shell->exit_code);
}
