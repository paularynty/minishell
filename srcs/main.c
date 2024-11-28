/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:07:14 by prynty            #+#    #+#             */
/*   Updated: 2024/12/11 15:56:00 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "./parser/parser.h"

//global variable to carry the exit status. mrworldwide for now
//sig_atomic_t = atomic relative to signal handling
//(we can also just pass around the exit code in the struct, 
//let's decide on that later)
sig_atomic_t	g_mrworldwide = 0;
#include "./parser/parser.h"

//global variable to carry the exit status. mrworldwide for now
//sig_atomic_t = atomic relative to signal handling
//(we can also just pass around the exit code in the struct, 
//let's decide on that later)
__sig_atomic_t	g_mrworldwide;

void	minishell(t_mini *shell)
{
	char	*line;
	char	prompt[1024];
	t_command	*commands;

	while (TRUE)
	{
		//update env;
		//if lexer and parser = gucci, execute;
		get_prompt(shell, prompt, sizeof(prompt));
		if (isatty(STDIN_FILENO))
		{
			line = readline(prompt);
			printf("1 TSEKKI\n");
			if (*line)
			{
				prep_command(shell, line);
				builtin_id = builtins(line);
				if (builtin_id) // 0 = BUILTIN_NONE, everything else is builtin
					handle_builtin(builtin_id, shell, line);
				add_history(line);
				execute(shell);
				printf("line on: %s\n", line);
				commands = tokenizer(line);
				printf("tokenizer onnistui :)\n");
				print_list(commands);
				free_commands(commands);
				free(line);
			}
			if (line == NULL)
				break ;
		}
	}
	free(line);
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
	exit(g_mrworldwide); //or mini.exit_code, whatever we decide
}
