/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:00:21 by prynty            #+#    #+#             */
/*   Updated: 2024/11/18 15:39:11 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup(t_mini *shell)
{
	ft_free_array(&shell->env);
	free(shell->cwd);
	shell->cwd = NULL;
	shell->heredoc = NULL;
}
