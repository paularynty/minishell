#include "minishell.h"

void	handle_builtin(int id, t_mini *shell)
{
	int	code;

	signal_reset();
	code = 0;
	// if (id == BUILTIN_CD)
	// 	code = builtin_cd(shell);
	if (id == BUILTIN_ECHO)
		code = builtin_echo(shell->cmd[0]);
	else if (id == BUILTIN_ENV)
		code = builtin_env(shell);
	else if (id == BUILTIN_EXIT)
		code = builtin_exit(shell, shell->cmd[0]);
	// else if (id == BUILTIN_EXPORT)
	// 	code = builtin_export(shell);
	else if (id == BUILTIN_PWD)
		code = builtin_pwd(shell);
	// else if (id == BUILTIN_UNSET)
	// 	code = builtin_unset(shell);
	shell->exit_code = code;
}

int	builtins(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (BUILTIN_CD);
	if (ft_strcmp(cmd, "echo") == 0)
		return (BUILTIN_ECHO);
	if (ft_strcmp(cmd, "env") == 0)
		return (BUILTIN_ENV);
	if (ft_strcmp(cmd, "exit") == 0)
		return (BUILTIN_EXIT);
	if (ft_strcmp(cmd, "export") == 0)
		return (BUILTIN_EXPORT);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (BUILTIN_PWD);
	if (ft_strcmp(cmd, "unset") == 0)
		return (BUILTIN_UNSET);
	return (BUILTIN_NONE);
}
