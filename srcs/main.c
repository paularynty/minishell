#include "minishell.h"

sig_atomic_t	g_mrworldwide = 0;

static void	setup_terminal(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
}

char	*setup_input(t_mini *shell)
{
	char	*input;
	char	prompt[1024];

	input = NULL;
	get_prompt(shell, prompt, sizeof(prompt));
	if (isatty(fileno(stdin)))
		input = readline(prompt);
	return (input);
}

static void	minishell(t_mini *shell)
{
	char		*input;
	t_command	*commands;

	while (TRUE)
	{
		input = setup_input(shell);
		if (input == NULL)
			break ;
		if (*input)
		{
			add_history(input); //this could be moved somewhere in parsing/exec functions
			if (lexer(shell, input))
			{
				commands = tokenizer(shell, shell->input);
				if (!commands)
					continue ;
				execute(shell, commands);
			//		free_commands(commands); // I think freeing command list should be right after executing?
			}
			else
			{
				if (input && *input)
					free(input);
			}
			if (shell->exit_flag || shell->abort)
				break ;
		}
		shell->cmd_count = 0; // move to execute
		input = NULL;
	}
	//clean_commands(commands);
}

int	main(int argc, char **argv, char **env)
{
	t_mini		shell;

	(void)argc;
	(void)argv;
	setup_terminal();
	if (!setup(&shell, env))
	{
		ft_putstr_fd("minishell: initialization error", STDERR_FILENO);
		cleanup(&shell);
		shell.exit_code = EXIT_FAILURE;
	}
	minishell(&shell);
	if (shell.abort)
	{
		ft_putstr_fd("minishell: aborting, critical error encountered\n", STDERR_FILENO);
		shell.exit_code = EXIT_FAILURE;
	}
	rl_clear_history();
	cleanup(&shell);
	return (shell.exit_code);
}
