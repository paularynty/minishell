#include "minishell.h"

sig_atomic_t	g_mrworldwide = 0;

static void	minishell(t_mini *shell)
{
	char		*input;
	char		prompt[1024];
	t_command	*commands;

	while (TRUE)
	{
		get_prompt(shell, prompt, sizeof(prompt));
		input = readline(prompt);
		if (input == NULL)
			break ;
		if (*input)
		{
			add_history(input); //this could be moved somewhere in parsing/exec functions
			if (lexer(shell, input))
				commands = tokenizer(shell->input);
			else
			{
				free(input);
				continue ;
			}
		//	print_list(commands);
			printf("Before execution\n");
			execute(shell, commands);
			if (shell->exit_flag)
				break ;
		}
		// free(input);
		input = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	shell;

	(void)argc;
	(void)argv;
	if (!setup(&shell, env))
		return (cleanup(&shell), 1);
	init_signals();
	minishell(&shell);
	rl_clear_history();
	cleanup(&shell);
	return (shell.exit_code);
}
