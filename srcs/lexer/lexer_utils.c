#include "minishell.h"

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
