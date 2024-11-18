/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:11:39 by prynty            #+#    #+#             */
/*   Updated: 2024/11/18 16:20:44 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_exit(t_mini *shell, char *line)
{
	if (ft_strcmp(line, "exit") == 0)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		shell->exit_flag = TRUE;
	}
}
