#include "minishell.h"

void	sig_handler_child(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	sig_handler_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_mrworldwide = signal;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_mrworldwide = signal;
		printf("\n");
		return ;
	}
}
