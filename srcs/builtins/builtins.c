/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:06:37 by prynty            #+#    #+#             */
/*   Updated: 2024/11/25 10:53:34 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_builtin(int id, t_mini *shell, char *line)
{
	if (id == BUILTIN_CD)
		builtin_cd(shell, line);
	if (id == BUILTIN_ECHO)
		builtin_echo(line);
	if (id == BUILTIN_ENV)
		builtin_env(shell->env);
	if (id == BUILTIN_EXIT)
		builtin_exit(shell, line);
	// if (id = BUILTIN_EXPORT)
	// 	builtin_export();
	if (id == BUILTIN_PWD)
		builtin_pwd(shell); //only one line in this func, so can just move it here later
	// if (id = BUILTIN_UNSET)
	// 	builtin_unset();
}

int	builtins(char *line)
{
	if (ft_strncmp(line, "cd", 2) == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(line, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(line, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(line, "exit") == 0)
		return (BUILTIN_EXIT);
	if (ft_strcmp(line, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(line, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(line, "unset") == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}
