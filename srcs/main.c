/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:07:14 by prynty            #+#    #+#             */
/*   Updated: 2024/11/25 14:28:33 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//global variable to carry the exit status. mrworldwide for now
//sig_atomic_t = atomic relative to signal handling
//(we can also just pass around the exit code in the struct, 
//let's decide on that later)
__sig_atomic_t	g_mrworldwide;

void	minishell(t_mini *shell)
{
	char	*line;
	char	prompt[1024];
	int		builtin_id;

	while (TRUE)
	{
		//update env;
		//if lexer and parser = gucci, execute;
		get_prompt(shell, prompt, sizeof(prompt));
		if (isatty(STDIN_FILENO))
		{
			line = readline(prompt);
			if (*line)
			{
				builtin_id = builtins(line);
				if (builtin_id) // 0 = BUILTIN_NONE, everything else is builtin
					handle_builtin(builtin_id, shell, line);
				if (shell->exit_flag)
					break ;
				add_history(line);
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
		return (1); // return (cleanup(&shell, 1));
	init_signals();
	minishell(&shell);
	rl_clear_history();
	cleanup(&shell);
	exit(g_mrworldwide); //or mini.exit_code, whatever we decide
}
