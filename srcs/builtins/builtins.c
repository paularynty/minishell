/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:06:37 by prynty            #+#    #+#             */
/*   Updated: 2024/11/18 16:20:33 by prynty           ###   ########.fr       */
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
	if (ft_strcmp(line, "pwd") == 0)
		builtin_pwd(shell); //only one line in this func, so can just move it here later
	// if (ft_strcmp(line, "unset") == 0)
	// 	builtin_unset();
}
