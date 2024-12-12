#include "../../includes/minishell.h"

//if you create with export something, it goes to env
//if you say export var XXX, it goes to pending list
//in unset you need to keep track to remove both from env and pending list

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

int	builtin_unset(t_mini *shell)
{
	if (!shell->cmd[1])
		return (0);
	else
		env_unset_variable(shell->env, shell->cmd[1]);
	return (0);
}
