/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:40 by prynty            #+#    #+#             */
/*   Updated: 2024/12/11 12:32:37 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_for_children(t_mini *shell, pid_t pid)
{
	int		status;

	if (waitpid(pid, &status, 0) == -1)
	{
		shell->exit_code = 1;
		perror("waitpid failed");
	}
	else if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	return (shell->exit_code);
}

bool	is_dir(char *path)
{
    struct stat	sb;

    if (stat(path, &sb) == -1)
        return (false);
    return (S_ISDIR(sb.st_mode));
}

int	check_access(t_mini *shell, char *cmd, char **cmd_array)
{
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			errno = ENOENT;
		else
			errno = 0;
		return (error_cmd(shell, cmd, cmd_array));
	}
	if (is_dir(cmd) == true)
	{
		errno = EISDIR;
		return (error_cmd(shell, cmd, cmd_array));
	}
	if (access(cmd, X_OK) == -1)
	{	
		errno = EACCES;
		return (error_cmd(shell, cmd, cmd_array));
	}
	return (0);
}
