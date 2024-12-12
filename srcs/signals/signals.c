#include "minishell.h"

void	signal_heredoc(int signal)
{
	close(STDIN_FILENO);
	g_mrworldwide = signal;
}

void	signal_ctrl_c(int signal)
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
	signal(SIGQUIT, SIG_IGN);
}
