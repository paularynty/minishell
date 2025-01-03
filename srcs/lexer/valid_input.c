#include "minishell.h"

int 	str_is_whitespace(const char *str)
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
	int	doubleq;

	single = 0;
	doubleq = 0;
	while (*str)
    {
		if (*str == '\'' && doubleq % 2 == 0) // double quotes aren't open, so increase singles.
			single++;
		else if (*str == '"' && single % 2 == 0) // single quotes aren't open, so we increase doubleqs.
			doubleq++;
		str++;
	}
	if (single % 2 != 0)
	{
		ft_putstr_fd("minishell: unmatched `'' marks.\n", 2);
		return (FALSE);
	}
	if (doubleq % 2 != 0)
	{
		ft_putstr_fd("minishell: unmatched '\"' marks.\n", 2);
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
			redir = input[i];
			i++;
			if ((redir == '>' && input[i] == '>') || (redir == '<' && input[i] == '<'))
				i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (!input[i] || input[i] == '\n' || ft_strchr("|><", input[i]))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

void	invalid_pipes_message(int pipes)
{
	if (pipes >= 2 && pipes <= 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (pipes > 3)
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
}

int	valid_pipes(const char *input)
{
	int		i;
	int		pipes;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
		pipes = 0;
		while (input[i] && input[i] == '|')
		{
			pipes++;
			i++;
		}
		if (pipes >= 2)
		{
			invalid_pipes_message(pipes);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	closed_pipes(const char *input)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
		if (input[i] == '|')
		{
			if (str_is_whitespace(input + i + 1))
			{
				ft_putstr_fd("minishell: unmatched '|' marks.\n", 2);
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}
