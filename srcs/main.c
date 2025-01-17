#include "minishell.h"

volatile sig_atomic_t	g_mrworldwide = 0;

//THIS IS FOR LARGE MINISHELL TESTER, REPLACE THIS SETUP_INPUT 
//WITH THE ONE BELOW BEFORE RUNNING THE TESTER
// static char	*setup_input(t_mini *shell)
// {
// 	char	*input;
// 	char	prompt[1024];

// 	input = NULL;
// 	get_prompt(shell, prompt, sizeof(prompt));
// 	if (isatty(fileno(stdin)))
// 		input = readline(prompt);
// 	else
// 	{
// 		char	*line;
// 		line = get_next_line(fileno(stdin));
// 		input = ft_strtrim(line, "\n");
// 		free(line);
// 	}
// 	add_history(input);
// 	return (input);
// }

static char	*setup_input(t_mini *shell)
{
	char	*input;
	char	prompt[1024];

	input = NULL;
	get_prompt(shell, prompt, sizeof(prompt));
	input = readline(prompt);
	if (input && *input)
		add_history(input);
	return (input);
}

static void	minishell(t_mini *shell)
{
	char	*input;
	t_cmd	*cmds;

	while (TRUE)
	{
		sig_init(&sig_handler_sigint);
		input = setup_input(shell);
		if (input == NULL)
			break ;
		if (*input)
		{
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
				execute(shell, cmds);
		}
		shell->cmd_count = 0;
	}
}

// static void	minishell(t_mini *shell)
// {
// 	char	*input;
// 	t_cmd	*cmds;

// 	while (TRUE)
// 	{
// 		//reset_signals();
// 		input = setup_input(shell);
// 		if (input == NULL)
// 			break ;
// 		if (*input)
// 		{
// 			if (lexer(shell, input))
// 			{
// 				cmds = tokenizer(shell, shell->input);
// 				if (cmds)
// 					execute(shell, cmds);
// 			}
// 			else if (input && *input)
// 				free(input);
// 		}
// 		shell->cmd_count = 0;
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_mini		shell;

	(void)argc;
	(void)argv;
	if (!setup(&shell, env))
	{
		ft_putstr_fd("minishell: initialization error\n", STDERR_FILENO);
		ft_free_array(&shell.env);
		exit(EXIT_FAILURE);
	}
	minishell(&shell);
	return (shell.exit_code);
}
