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
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
