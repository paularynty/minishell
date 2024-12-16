#include "minishell.h"

int	backslash(const char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
		if (input[i] == '\\')
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `\'", 2);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}