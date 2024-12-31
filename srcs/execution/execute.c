#include "minishell.h"

static int	exec_parent(t_mini *shell, t_command *command, int is_builtin)
{
	handle_builtin(is_builtin, shell, command);
	return (TRUE);
}

/*Initializes pipeline.
Sends a list element to fork_and_execute.
Closes all pipes and moves onto the next node.
Waits for children to finish, cleans up and returns the last exit code.*/
static int	exec_child(t_mini *shell, t_command *command)
{
	t_command	*curr;

	if (!init_pipeline(shell))
		return (FALSE);
	curr = command;
	while (curr)
	{
		if (fork_and_execute(shell, curr) == -1)
			return (FALSE);
		signal_child();
		close_all_pipes(shell, curr->cmd_i);
		curr = curr->next;
	}
	wait_for_children(shell);
	cleanup_success(shell);
	return (shell->exit_code);
}

/*Checks if the command of the very first t_cmd node is a builtin.
If it is a builtin and there is only one command, it is executed in the parent.
Otherwise, we move onto exec_child to fork and execute commands as necessary.*/
int	execute(t_mini *shell, t_command *command)
{
	t_command	*curr;
	int			is_builtin;

	is_builtin = builtins(command->cmd[0]);
	if (shell->cmd_count == 1 && is_builtin)
		exec_parent(shell, command, is_builtin);
	else
		exec_child(shell, command); // what if it fails?
	// Free the cmd arrays in each command node (will move this to its own function later)
	curr = command;
	while (curr)
	{
		ft_free_array(&curr->cmd);
		curr = curr->next;
	}
	return (shell->exit_code);
}
