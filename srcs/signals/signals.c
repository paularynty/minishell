/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:09:39 by prynty            #+#    #+#             */
/*   Updated: 2024/11/18 11:48:45 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_ctrl_d(int signal)
{	
	if (signal == SIGQUIT)
		exit(1);
}

static void	signal_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, signal_ctrl_d);
}
