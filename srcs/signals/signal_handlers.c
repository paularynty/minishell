#include "minishell.h"

void	signal_handler_heredoc(int signal)
{
	close(STDIN_FILENO);
	g_mrworldwide = signal;
}

void	signal_handler_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_mrworldwide = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}
