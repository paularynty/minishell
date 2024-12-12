#include "../../includes/minishell.h"

// env takes in no args, only prints the env list
// when running env -i ./minishell and env as command
// env list should only be PWD, SHLVL and _=/usr/bin/env
int	builtin_env(t_mini *shell)
{
	int	i;

	i = 0;
	if (!env_get_variable(shell->env, "PATH"))
	{
		error_builtin(ENV, NULL, "No such file or directory");
		return (127);	
	}
	while (shell->env && shell->env[i])
	{
		if (ft_strchr(shell->env[i], '='))
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}
