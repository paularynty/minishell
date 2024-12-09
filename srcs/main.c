/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:07:14 by prynty            #+#    #+#             */
/*   Updated: 2024/12/09 12:50:25 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//global variable to carry the exit status. mrworldwide for now
//sig_atomic_t = atomic relative to signal handling
//(we can also just pass around the exit code in the struct, 
//let's decide on that later)
__sig_atomic_t	g_mrworldwide;

static int	add_input(t_mini *shell, char *input)
{
	char	*temp;
	
	if (shell->input)
	{
		temp = ft_strjoin(shell->input, temp);
		if (!temp)
		{
			perror("minishell: failed to join input");
			return (FALSE);
		}
		free(shell->input);
		shell->input = temp;
	}
	else
	{
		shell->input = ft_strdup(input);
		if (!shell->input)
		{
			perror("minishell: failed to add input");
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	minishell(t_mini *shell)
{
	char	*input;
	char	prompt[1024];

	while (TRUE)
	{
		//update env;
		get_prompt(shell, prompt, sizeof(prompt));
		input = readline(prompt);
		if (input == NULL)
			break ;
		if (*input)
		{
			if (!add_input(shell, input))
			{
				free(input);
				continue ;
			}
			// if (lexer && parser)
			execute(shell, input);
			add_history(input); //this could be moved somewhere in parsing/exec functions
			if (shell->exit_flag)
				break ;
		}
		free(input);
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
