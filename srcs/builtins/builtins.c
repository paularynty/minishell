/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:06:37 by prynty            #+#    #+#             */
/*   Updated: 2024/11/27 16:08:47 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_builtin(int id, t_mini *shell, char *line)
{
	char	**cmd;
	
	cmd = ft_split(line, ' ');
	if (!cmd)
		ft_free_array(&cmd);
	if (id == BUILTIN_CD)
		builtin_cd(shell, cmd);
	if (id == BUILTIN_ECHO)
		builtin_echo(cmd);
	if (id == BUILTIN_ENV)
		builtin_env(shell->env);
	if (id == BUILTIN_EXIT)
		builtin_exit(shell, cmd);
	if (id == BUILTIN_EXPORT)
		builtin_export(shell);
	if (id == BUILTIN_PWD)
		builtin_pwd(shell); //only one line in this func, so can just move it here later
	// if (id = BUILTIN_UNSET)
	// 	builtin_unset();
}

int	builtins(char *line)
{
	if (ft_strncmp(line, "cd", 2) == 0)
		return (BUILTIN_CD);
	if (ft_strncmp(line, "echo", 4) == 0)
		return (BUILTIN_ECHO);
	if (ft_strncmp(line, "env", 3) == 0)
		return (BUILTIN_ENV);
	if (ft_strncmp(line, "exit", 4) == 0)
		return (BUILTIN_EXIT);
	if (ft_strncmp(line, "export", 6) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strncmp(line, "pwd", 3) == 0)
		return (BUILTIN_PWD);
	if (ft_strncmp(line, "unset", 5) == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}
