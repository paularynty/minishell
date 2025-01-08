#include "minishell.h"

static void	signal_handler_heredoc(int signal)
{
	close(STDIN_FILENO);
	g_mrworldwide = signal;
}

void	signal_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, signal_handler_heredoc);
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

static void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2); 
}

void	signal_child(void)
{
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
}

void	signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_init(void)
{
	signal(SIGINT, signal_handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}
