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
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `\\'\n", 2);
			shell->exit_code = 2;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	matching_quotes(t_mini *shell, const char *str)
{
	int	single;
	int	doubleq;

	single = 0;
	doubleq = 0;
	while (*str)
	{
		if (*str == '\'' && doubleq % 2 == 0)
			single++;
		else if (*str == '"' && single % 2 == 0)
			doubleq++;
		str++;
	}
	if (single % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `''\n", 2);
		shell->exit_code = 2;
		return (FALSE);
	}
	if (doubleq % 2 != 0)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '\"'\n", 2);
		shell->exit_code = 2;
		return (FALSE);
	}
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
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				shell->exit_code = 2;
				return (FALSE);
			}
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
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				shell->exit_code = 2;
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}
