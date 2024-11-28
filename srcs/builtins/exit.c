/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:39 by prynty            #+#    #+#             */
/*   Updated: 2024/12/11 15:42:19 by sniemela         ###   ########.fr       */
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
//

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
