#include "minishell.h"

static void	exec_forked_builtin(t_mini *shell, t_cmd *cmd, int is_builtin)
{
	// if (!save_std(shell))
	// 	debug_print("Failed to save std\n");
	handle_builtin(is_builtin, shell, cmd); //rework this to take in account failed builtin exec
	// if (!reset_std(shell))
	// 	debug_print("Failed to reset std\n");
	// cleanup_success(shell);
	exit(EXIT_SUCCESS);
}

/* Executes command in child process. 
Upon successful execve() call, exits with EXIT_SUCCESS (0). 
Otherwise cleans everything and exits with predetermined exit code.*/
// static void	exec_forked_cmd(t_mini *shell, t_cmd *cmd, int i)
static void	exec_forked_cmd(t_mini *shell, t_cmd *cmd)
{
	char	*cmd_path;
	
	cmd_path = get_cmd_path(shell, cmd->cmds[0]);
	if (!cmd_path)
		check_access(shell, cmd->cmds[0]);
	else
		check_access(shell, cmd_path);
	signal_reset();
	// debug_print("sending to execve: %s\n", cmd->cmds[0]);
	if (execve(cmd_path, cmd->cmds, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, cmd->cmds[0], strerror(errno), errno);
	}
}

int	fork_and_execute(t_mini *shell, t_cmd *cmd)
{
	int	is_builtin;

	// debug_print("cmd_i: %d\n", cmd->cmd_i);
	is_builtin = builtins(cmd->cmds[0]);
	signal_reset();
	shell->pids[cmd->cmd_i] = fork();
	if (shell->pids[cmd->cmd_i] == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (shell->pids[cmd->cmd_i] == 0)
	{
		// debug_print("Child process %d created (PID: %d)\n", cmd->cmd_i, getpid());
		close_unused_fds(shell, cmd->cmd_i);
		if (!resolve_fds(shell, cmd))
		{
			debug_print("failed to resolve fds\n");
			return (FALSE);
		}
		check_print("After resolving fd's\n");
		check_print("Command nro %d's input_fd: %d\n", cmd->cmd_i, cmd->input_fd);
		check_print("Command nro %d's output_fd: %d\n", cmd->cmd_i, cmd->output_fd);
		if (!dup_input(shell, cmd, cmd->cmd_i))
			debug_print("failed to dup input\n");
		if (!dup_output(shell, cmd, cmd->cmd_i))
			debug_print("failed to dup output\n");
		if (builtins(cmd->cmds[0])) //check for builtin cmd in pipe
			exec_forked_builtin(shell, cmd, is_builtin);
		else
			// exec_forked_cmd(shell, cmd, i);
			exec_forked_cmd(shell, cmd);
	}
	return (TRUE);
}

static int	exec_parent(t_mini *shell, t_cmd *cmd, int is_builtin)
{
	handle_builtin(is_builtin, shell, cmd);
	return (TRUE);
}

/*Initializes pipeline.
Sends a list element to fork_and_execute.
Closes all pipes and moves onto the next node.
Waits for children to finish, cleans up and returns the last exit code.*/
static int	exec_child(t_mini *shell, t_cmd *cmd)
{
	t_cmd	*curr;

	if (!init_pipeline(shell))
		return (FALSE);
	curr = cmd;
	while (curr)
	{
		//sig_handler_reseted();
		signal_child();
		if (fork_and_execute(shell, curr) == -1)
			return (FALSE);
		close_all_pipes(shell, curr->cmd_i);
		curr = curr->next;
	}
	shell->exit_code = wait_for_children(shell);
	cleanup_success(shell);
	return (TRUE);
}

/*Checks if the command of the very first t_cmd node is a builtin.
If it is a builtin and there is only one command, it is executed in the parent.
Otherwise, we move onto exec_child to fork and execute commands as necessary.*/
int	execute(t_mini *shell, t_cmd *cmd)
{
	int			is_builtin;

	is_builtin = builtins(cmd->cmds[0]);
	if (shell->cmd_count == 1 && is_builtin)
		exec_parent(shell, cmd, is_builtin);
	else
		exec_child(shell, cmd); // what if it fails?
	return (shell->exit_code);
}
