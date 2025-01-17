#include "minishell.h"

int	char_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (TRUE);
	else
		return (FALSE);
}

int	char_is_whitespace(char c)
{
	if (c != 32 && (c < 9 || c > 13))
		return (FALSE);
	return (TRUE);
}

void	error_pipes(t_mini *shell, int pipes)
{
	if (pipes >= 2 && pipes <= 3)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		shell->exit_code = 2;
	}
	else if (pipes > 3)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `||'\n", 2);
		shell->exit_code = 2;
	}
}

int	str_is_whitespace(const char *str)
{
	while (*str)
	{
		if (*str != 32 && (*str < 9 || *str > 13))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
