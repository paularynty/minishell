/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:00:21 by prynty            #+#    #+#             */
/*   Updated: 2024/12/09 12:39:21 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup(t_mini *shell)
{
	ft_free_array(&shell->env);
	// ft_free_array(&shell->cmd);
	free(shell->input);
	shell->input = NULL;
	free(shell->cwd);
	shell->cwd = NULL;
	shell->heredoc = NULL;
}
