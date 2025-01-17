#include "minishell.h"

int	builtin_echo(char **cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
	{
		newline = FALSE;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
