#include "minishell.h"

static int	exec_parent(t_mini *shell, int is_builtin)
{
	handle_builtin(is_builtin, shell);
	return (TRUE);
}

static int	exec_child(t_mini *shell, t_command *command)
{
	int	i;

	i = 0;
	if (!init_pipeline(shell))
		return (FALSE);
	while (i < shell->cmd_count)
	{
		if (fork_and_execute(shell, command, i) == -1)
			return (FALSE);
		signal_child();
		close_all_pipes(shell, i);
		i++;
		command = command->next;
	}
	wait_for_children(shell);
	cleanup_success(shell);
	return (shell->exit_code);
}

//TO DO: up until a pipe, only the first token can be CMD
//the next ones after that (excl. redires etc.) are ARG
//so that executor works as it should
int	execute(t_mini *shell, t_command *commands)
{
	int		is_builtin;
	int		i;

	i = 0;
	shell->cmd = extract_all_commands(shell, commands);
	while (i < shell->cmd_count)
	{
		is_builtin = builtins(shell->cmd[i][0]);
		i++;
	}
	if (shell->cmd_count == 1 && is_builtin)
		exec_parent(shell, is_builtin);
	else
		exec_child(shell, commands);
	ft_free_array(shell->cmd);
	return (shell->exit_code);
}
