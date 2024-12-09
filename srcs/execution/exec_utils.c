/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:40 by prynty            #+#    #+#             */
/*   Updated: 2024/12/09 10:41:10 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_for_children(t_mini *shell, pid_t pid)
{
	int	status;
	int	retval;
	int	wait_count;

	wait_count = 2;
	while (wait_count > 0)
	{
		retval = waitpid(-1, &status, 0);
		if (retval == -1)
		{
			shell->exit_code = 1;
			perror("waitpid failed");
			break ;
		}
		wait_count--;
		if (retval == pid && WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
	}
	return (shell->exit_code);
}
