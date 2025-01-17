#include "minishell.h"

int	builtin_pwd(t_mini *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		error_builtin(PWD, NULL, "cannot access current directory");
		return (1);
	}
	printf("%s\n", shell->cwd);
	free(cwd);
	return (0);
}
