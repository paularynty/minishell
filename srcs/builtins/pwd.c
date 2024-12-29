#include "minishell.h"
//TO DO: need to update pwd in env as well

int	builtin_pwd(t_mini *shell)
{
	printf("%s\n", shell->cwd);
	return (0);
}
