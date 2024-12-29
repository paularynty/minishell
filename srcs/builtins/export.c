#include "minishell.h"

//if just export, you add to pending list, which is different from env
//you can export multiple vars in a single command

//TO DO:
//check for valid export
//when adding new export variable, put it in alphabetical order
//when calling export [arg], give prompt back if successful
//and only print export if it's a standalone command
//need to be able to export multiple variables

int	valid_export(char *str)
{
	if (*str == '\0' || *str == '=' || ft_isdigit(*str))
		return (FALSE);
	while (*str && *str != '=')
	{
		if (*str == '_')
		{
			str++;
			continue ;
		}
		if (!ft_isalnum(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	sort_export_table(char **env)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*temp;

	i = 0;
	size = count_array_elements(env);
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	export_variable(t_mini *shell, char *arg)
{
	char	*value;

	if (!valid_export(arg))
		return (-1);
	value = ft_strchr(arg, '=');
	if (!value)
	{
		env_set_variable(shell, arg, "");
		return (FALSE);
	}
	*value++ = '\0';
	env_unset_variable(shell->env, arg);
	env_set_variable(shell, arg, value);
	return (TRUE);
}

static int	print_export_vars(char **env)
{
	int		i;
	char	*equal_char;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (env[i][0] != '\0')
		{
			equal_char = ft_strchr(env[i], '=');
			if (equal_char)
			{
				write(STDOUT_FILENO, env[i], (equal_char - env[i]) + 1);
				printf("\"%s\"\n", equal_char + 1);
			}
			else
				printf("%s\n", env[i]);
		}
		i++;
	}
	return (TRUE);
}

int	builtin_export(t_mini *shell, t_command *command)
{
	char	**temp;
	int		i;

	i = 1;
	temp = clone_env(shell->env);
	if (!temp)
		return (-1);
	sort_export_table(temp);
	if (!command->cmd[1])
		return (print_export_vars(temp));
	while (command->cmd[i])
	{
		if (!export_variable(shell, command->cmd[i]))
		{
			// error_export(shell->cmd[i]);
			shell->exit_code = 1;
		}
		i++;
	}
	ft_free_array(&temp);
	return (shell->exit_code);
}
