#include "minishell.h"

volatile sig_atomic_t	g_mrworldwide = 0;

//THIS IS FOR LARGE MINISHELL TESTER, REPLACE THIS SETUP_INPUT WITH THE ONE BELOW BEFORE RUNNING THE TESTER
static char	*setup_input(t_mini *shell)
{
	char	*input;
	char	prompt[1024];

	input = NULL;
	get_prompt(shell, prompt, sizeof(prompt));
	if (isatty(fileno(stdin)))
		input = readline(prompt);
	else
	{
		char	*line;
		line = get_next_line(fileno(stdin));
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}

// static char	*setup_input(t_mini *shell)
// {
// 	char	*input;
// 	char	prompt[1024];

// 	input = NULL;
// 	get_prompt(shell, prompt, sizeof(prompt));
// 	input = readline(prompt);
// 	return (input);
// }

static void	minishell(t_mini *shell)
{
	char	*input;
	t_cmd	*cmds;

	while (TRUE)
	{
		//reset_signals();
		input = setup_input(shell);
		if (input == NULL)
			break ;
		if (*input)
		{
			add_history(input); //this could be moved somewhere in parsing/exec functions
			if (!lexer(shell, input))
			{
				if (input && *input)
				{
					free(input);
					continue ;
				}
			}
			cmds = tokenizer(shell, shell->input);
			if (cmds)
			{
				// print_list(cmds);
				execute(shell, cmds);
			}
		}
		shell->cmd_count = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini		shell;

	(void)argc;
	(void)argv;
	if (!setup(&shell, env))
	{
		ft_putstr_fd("minishell: initialization error", STDERR_FILENO);
		// cleanup(&shell); //need to check how to clean commands here if cmd is not yet initialized in main
		shell.exit_code = EXIT_FAILURE;
	}
	minishell(&shell);
	if (shell.abort)
	{
		ft_putstr_fd("minishell: aborting, critical error encountered\n", STDERR_FILENO);
		//cleanup(&shell); //is this needed?
		shell.exit_code = EXIT_FAILURE;
	}
	return (shell.exit_code);
}
