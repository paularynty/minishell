//TO DO: need to update pwd in env as well

#include "../../includes/minishell.h"

int	builtin_pwd(t_mini *shell)
{
	printf("%s\n", shell->cwd);
	return (0);
}
