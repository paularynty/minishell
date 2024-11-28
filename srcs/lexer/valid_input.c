/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:58:58 by sniemela          #+#    #+#             */
/*   Updated: 2024/11/22 11:37:24 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//bad pipes
//unclosed quotes
//passing empty line
//inv redirection

int iswhitespace(const char *str)
{
	while (*str)
	{
		if (*str != 32 && (*str < 9 || *str > 13))
			return (0);
		str++;
	}
	return (1);
}

int	matching_quotes(const char *str)
{
	int	single;
	int	double;

	single = 0;
	double = 0;
	while (*str)
    {
		if (*str == 39 && double % 2 == 0) // didn't accept ''', so used ASCII val. Double quotes aren't open, so increase singles.
			single++;
		else if (*str == '"' && single % 2 == 0) // single quotes aren't open, so we increase doubles.
			double++;
		str++;
	}
	if (single % 2 != 0)
	{
		ft_putstr_fd("minishell: unmatched `'' marks", 2); // print matching error message here		
		return (FALSE);
	}
	if (double % 2 != 0)
	{
		ft_putstr_fd("minishell: unmatched '\"' marks", 2); // cant use ft_putstr_fd, need to make ft_printf_fd to get '"' printed.
		return (FALSE);
	}
	return (TRUE);
}

int valid_redirection(const char *input)
{
	int		i;
	char	redir;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			redir == input[i];
			i++;
			if ((redir == '>' && input[i] == '>') || (redir == '<' && input[i] == '<'))
				i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i] || input[i] == '\n' || ft_strchr("|><", input[i]))
			{
				// Print error message ***/**** (bash version down below) // need separate function for this
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

***
// prompt> ls >>             
// bash: syntax error near unexpected token `newline'

****
// prompt> ls << 
// bash: syntax error near unexpected token `newline'
// prompt> ls < |
// bash: syntax error near unexpected token `|'

/*******************************
 * 
 * PIPE ERROR MESSAGES DEPEND ON WETHER THEY COME AFTER A REDIRECTION (inv redir) OR ARE INVALID PIPES
 * 
prompt>$ ls < | echo hello
bash: syntax error near unexpected token `|'
prompt>$ ls < || echo hello
bash: syntax error near unexpected token `||'
prompt>$ ls < ||| echo hello
bash: syntax error near unexpected token `||'
prompt>$ ls < |||| echo hello
bash: syntax error near unexpected token `||'
prompt>$ ls ||| echo hello
bash: syntax error near unexpected token `|'
prompt>$ ls |||| echo hello
bash: syntax error near unexpected token `||'
prompt>$ ls |||||| echo hello
bash: syntax error near unexpected token `||'

******************************/

int	valid_pipes(const char *input)
{
	int		i;
	int		pipes;

	i = 0;
	while (input[i])
	{
		pipes = 0;
		while (input[i] && input[i] == '|')
		{
			pipes++;
			i++;
		}
		if (pipes == 3)
		{
			// print error message "minishell: syntax error near unexpected token `|'"
			return (FALSE);
		}
		if (pipes > 3)
		{
			// print error message "minishell: syntax error near unexpected token `||'"
			return (FALSE);	
		}
		i++;
	}
	return (TRUE);
}

// This is the first argument validation check.
// We check whether the prompt is empty/whitespace, contains uneven quotes or other errors we can handle immediately
// without taking into account pipes. Upon occuring, we send correct error message, update add_history and return matching exit code.
// Add exit_code / error message handling later.

int valid_input(char *input)
{
	if (iswhitespace(input))
		return (FALSE); // handle whitespace separately? To an exit_function which frees any allocated memory, in bash history is added, rl_on_newline()
	if (!matching_quotes(input))
		return (FALSE);
	if (!valid_redirection(input))
		return (FALSE);
	if (!valid_pipes(input))
		return (FALSE);
}
