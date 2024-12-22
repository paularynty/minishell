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
		rl_replace_line("", 0);
		printf("\n");
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
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
