#include "minishell.h"

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = TRUE;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		newline = FALSE;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
