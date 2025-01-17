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
	while (*str)
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

static int	exit_extra_args(void)
{
	error_builtin(EXIT, NULL, "too many arguments");
	return (1);
}

int	builtin_exit(t_mini *shell, t_cmd *head, char **args)
{
	int	code;

	code = 0;
	if (isatty(STDIN_FILENO) && shell->cmd_count == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (args[1] == NULL)
	{
		rl_clear_history();
		cleanup_success_exit(shell, head);
		exit(shell->exit_code);
	}
	if (!is_numeric(args[1]))
		return (exit_non_numeric(args));
	if (args[2] != NULL)
		return (exit_extra_args());
	if (args[1])
		code = ft_atoi(args[1]);
	rl_clear_history();
	cleanup_success_exit(shell, head);
	exit(code);
}
