#include "minishell.h"

void	signal_heredoc(void)
{
	signal(SIGINT, signal_handler_heredoc);
	signal(SIGQUIT, signal_handler_heredoc);
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
