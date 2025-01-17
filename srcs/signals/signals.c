#include "minishell.h"

void	sig_heredoc(void *func)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = func;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_ignore(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = SIG_IGN;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_child(void *func)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = func;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = func;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_reset(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = SIG_DFL;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_DFL;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	sig_init(void *func)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = func;
	sigint.sa_flags = SA_SIGINFO;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = SA_SIGINFO;
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}
