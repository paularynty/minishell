/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:10:47 by prynty            #+#    #+#             */
/*   Updated: 2024/11/14 13:46:17 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	setup(t_mini *shell, char **env)
{
	shell->env = env; //env_clone function to clone the env 
	//so if unset is called in a nested minishell instance, it doesn't change/corrupt the original env variables
	//create env pending list, this can be a 2D array;
	shell->heredoc = NULL;
	shell->fd[0] = STDIN_FILENO;
	shell->fd[1] = STDOUT_FILENO;
	shell->exit_flag = FALSE;
	return (TRUE);
}
