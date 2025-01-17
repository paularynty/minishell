#include "minishell.h"

void	env_unset_variable(char **env, char *variable)
{
	int		i;
	size_t	var_len;

	if (!env || !variable || variable[0] == '\0')
		return ;
	i = 0;
	var_len = ft_strlen(variable);
	while (env[i])
	{
		if (ft_strncmp(env[i], variable, var_len) == 0)
		{
			if (*(env[i] + var_len) == '=' || *(env[i] + var_len) == '\0')
			{
				env[i][0] = '\0';
				return ;
			}
		}
		i++;
	}
}

int	builtin_unset(t_mini *shell, char **args)
{
	if (!args[1])
		return (0);
	else
		env_unset_variable(shell->env, args[1]);
	return (0);
}
