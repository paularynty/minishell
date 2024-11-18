/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:06:37 by prynty            #+#    #+#             */
/*   Updated: 2024/11/12 16:04:41 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtins(t_mini *shell, char *line)
{
    // if (ft_strcmp(line, "cd") == 0)
	// 	builtin_cd();
	// if (ft_strcmp(line, "echo") == 0)
	// 	builtin_echo();
	if (ft_strcmp(line, "env") == 0)
		builtin_env(shell->env);
	if (ft_strcmp(line, "exit") == 0)
		builtin_exit(shell, line);
	// if (ft_strcmp(line, "export") == 0)
	// 	builtin_export();
	// if (ft_strcmp(line, "pwd") == 0)
	// 	builtin_pwd();
	// if (ft_strcmp(line, "unset") == 0)
	// 	builtin_unset();
}
