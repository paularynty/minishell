/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:39 by prynty            #+#    #+#             */
/*   Updated: 2024/11/25 15:25:50 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TO DO: 
//exit with more than one arg should print "minishell: exit: too many arguments"
//and exit code should be 1

void	builtin_exit(t_mini *shell, char **cmd)
{
	if (cmd[1])
		shell->exit_code = ft_atoi(cmd[1]);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(shell->exit_code);
}
