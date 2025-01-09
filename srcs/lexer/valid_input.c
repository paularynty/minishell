#include "minishell.h"

int	backslash(t_mini *shell, const char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quote_offset(input + i, input[i]);
		if (input[i] == '\\')
			return (error_syntax(shell, "\\"), TRUE);
		i++;
	}
	return (FALSE);
}

int	matching_quotes(t_mini *shell, const char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*str)
	{
		if (*str == '\'' && double_quote % 2 == 0)
			single_quote++;
		else if (*str == '"' && single_quote % 2 == 0)
			double_quote++;
		str++;
	}
	if (single_quote % 2 != 0)
		return (error_quotes(shell, "\'"), FALSE);
	if (double_quote % 2 != 0)
		return (error_quotes(shell, "\""), FALSE);
	return (TRUE);
}

int	valid_redirection(t_mini *shell, const char *input)
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
				return (error_syntax(shell, "newline"), FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	valid_pipes(t_mini *shell, const char *input)
{
	int		i;
	int		pipes;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quote_offset(input + i, input[i]);
		pipes = 0;
		while (input[i] && input[i] == '|')
		{
			pipes++;
			i++;
		}
		if (pipes >= 2)
			return (error_pipes(shell, pipes), FALSE);
		i++;
	}
	return (TRUE);
}

int	closed_pipes(t_mini *shell, const char *input)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quote_offset(input + i, input[i]);
		if (input[i] == '|')
		{
			if (str_is_whitespace(input + i + 1))
				return (error_syntax(shell, "|"), FALSE);
		}
		i++;
	}
	return (TRUE);
}
