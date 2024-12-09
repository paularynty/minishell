/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:19:59 by prynty            #+#    #+#             */
/*   Updated: 2024/12/05 14:44:45 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_builtin(char *builtin, char *str, char *error_str)
{
	char	buffer[1024];

	ft_strlcpy(buffer, "minishell: ", sizeof(buffer) - 1);
	ft_strlcat(buffer, builtin, sizeof(buffer) - 1);
	if (str)
	{
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
		ft_strlcat(buffer, str, sizeof(buffer) - 1);
	}
	if (!error_str)
		error_str = strerror(errno);
	if (error_str && error_str[0] != '\0')
	{
		ft_strlcat(buffer, ": ", sizeof(buffer) - 1);
		ft_strlcat(buffer, error_str, sizeof(buffer) - 1);
	}
	ft_strlcat(buffer, "\n", sizeof(buffer));
	ft_putstr_fd(buffer, STDERR_FILENO);
}

void	error_cmd(t_mini *shell, char *cmd, char **cmd_array)
{
	int	exitcode;

	exitcode = errno;
	ft_putstr_fd("minishell: ", 2);
	if (errno == EACCES || errno == ENOENT || errno == EISDIR)
		perror(cmd);
	else
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	if (cmd_array)
		ft_free_array(&cmd_array);
	// close_all(shell);
	if (exitcode == EACCES || exitcode == EISDIR)
		shell->exit_code = 126;
	else
		shell->exit_code = 127;
}
