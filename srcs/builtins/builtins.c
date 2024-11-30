/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:06:37 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 16:41:51 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_builtin(int id, t_mini *shell)
{
	int	code;

	code = 0;
	if (id == BUILTIN_CD)
		code = builtin_cd(shell);
	if (id == BUILTIN_ECHO)
		code = builtin_echo(shell->cmd);
	if (id == BUILTIN_ENV)
		code = builtin_env(shell->env);
	if (id == BUILTIN_EXIT)
		code = builtin_exit(shell);
	if (id == BUILTIN_EXPORT)
		code = builtin_export(shell);
	if (id == BUILTIN_PWD)
		code = builtin_pwd(shell); //only one line in this func, so can just move it here later
	if (id == BUILTIN_UNSET)
		code = builtin_unset(shell->cmd);
	shell->exit_code = code;
}

int	builtins(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (BUILTIN_CD);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (BUILTIN_ECHO);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (BUILTIN_ENV);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (BUILTIN_EXIT);
	if (ft_strncmp(cmd, "export", 6) == 0)
		return (BUILTIN_EXPORT);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (BUILTIN_PWD);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}
