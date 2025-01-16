#include "minishell.h"

int	builtin_pwd(t_mini *shell)
{
	printf("%s\n", shell->cwd);
	return (0);
}
