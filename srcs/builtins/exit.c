#include "minishell.h"

// exit without args:
// prints “exit\n” with exit code 0
// exit [numeric arg], e.g. exit 5:
// prints "exit\n", exit code is numeric arg
// exit w/ >1 arg:
// “exit\n minishell: exit: too many arguments”, exit code 1
// exit w/ non numeric args: 
// “exit\n minishell: exit: [arg]: numeric argument required”, exit code 2

//TO DO:
//handle "-" and "+"
//does the shell actually exit when too many args???
//if exit code given is larger than LONG_MAX, give error numeric arg required
//reset exit code after 255,

static int	is_numeric(char *str)
{
	if ((*str == '-' || *str == '+') && *(str + 1))
		str++;
	while (str != NULL)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static int	exit_non_numeric(char **args)
{
	error_builtin(EXIT, args[1], "numeric argument required");
	return (2);
}

static int	exit_extra_args(t_mini *shell)
{
	shell->exit_flag = FALSE;
	error_builtin(EXIT, NULL, "too many arguments");
	return (1);
}

int	builtin_exit(t_mini *shell, char **args)
{
	int	code;

	shell->exit_flag = TRUE;
	if (isatty(STDIN_FILENO) && shell->cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1] == NULL)
		return (shell->exit_code);
	// if (shell->cmd[0][1])
	// {
	// 	while (shell->cmd[0][1][i])
	// 	{
	// 		if (!ft_isdigit(shell->cmd[0][1][i]))
	// 			numeric_flag = TRUE;
	// 		i++;
	// 	}
	// 	code = ft_atoi(shell->cmd[0][1]);
	// }
	if (!is_numeric(args[1]))
		code = exit_non_numeric(args);
	if (count_array_elements(args) > 2)
		code = exit_extra_args(shell);
	else
		code = ft_atoi(args[1]);
	return (code);
}
