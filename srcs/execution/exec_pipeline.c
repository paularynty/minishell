#include "minishell.h"

/*	Frees PID array. */
// static void	free_pids(pid_t *pids)
// {
// 	size_t	i;

// 	i = 0;
// 	while (pids[i] >= 0)
// 	{
// 		free(pids[i]);
// 		i--;
// 	}
// 	free(pids);
// 	pids = NULL; //not sure if needed but adding this as muscle memory lmao
// }

// static void	close_all_pipes(int *fd)
// {
// 	if (!fd)
// 		return ;
// 	if (fd[0] >= 0)
// 		close(fd[0]);
// 	if (fd[1] >= 0)
// 		close(fd[1]);
// 	fd[0] = -1;
// 	fd[1] = -1;
// }

// void	close_all(t_mini *shell, t_command *command)
// {
// 	if (command->input_fd >= 0)
// 		close(command->input_fd);
// 	if (command->output_fd >= 0)
// 		close(command->output_fd);
// 	close(shell->pipe[0]);
// 	close(shell->pipe[1]);
// }

/* Frees pipes. */
static void	free_pipes(t_mini *shell, int i)
{
	while (i > 0)
	{
		i--;
		free(shell->pipes[i]);
	}
	free(shell->pipes);
	shell->pipes = NULL;
}

/* Closes all pipes. (Should also set to -1?) */
void	close_all_pipes(t_mini *shell, int i)
{
	if (shell->cmd_count > 1)
	{
		if (i == 0)
			close(shell->pipes[i][1]); //singular pipe, close its write end
		else if (i < shell->cmd_count - 1)
		{
			close(shell->pipes[i - 1][0]);
			close(shell->pipes[i][1]);
		}
		else if (i == shell->cmd_count - 1)
			close(shell->pipes[i - 1][0]);
	}
}

/*	Closes unused pipes.*/
void	close_unused_fds(t_mini *shell, int i)
{
	int	j;

	j = i + 1;
	if (shell->cmd_count >= 2 && i < shell->cmd_count - 1)
		close(shell->pipes[i][0]);
	while (j < shell->cmd_count - 1)
	{
		if (shell->pipes[j])
		{
			close(shell->pipes[j][0]);
			close(shell->pipes[j][1]);
		}
		j++;
	}
}

static void	exec_forked_builtin(t_mini *shell, t_command *command, int is_builtin)
{
	// if (!save_std(shell))
	// 	debug_print("Failed to save std\n");
	handle_builtin(is_builtin, shell, command); //rework this to take in account failed builtin exec
	// if (!reset_std(shell))
	// 	debug_print("Failed to reset std\n");
	// cleanup_success(shell);
	exit(EXIT_SUCCESS);
}

/* Executes command in child process. 
Upon successful execve() call, exits with EXIT_SUCCESS (0). 
Otherwise cleans everything and exits with predetermined exit code.*/
// static void	exec_forked_cmd(t_mini *shell, t_command *command, int i)
static void	exec_forked_cmd(t_mini *shell, t_command *command)
{
	char	*cmd_path;
	
	cmd_path = get_cmd_path(shell, command->cmd[0]);
	if (!cmd_path)
		check_access(shell, command->cmd[0]);
	check_access(shell, cmd_path);
	signal_reset();
	// debug_print("sending to execve: %s\n", command->cmd[0]);
	if (execve(cmd_path, command->cmd, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, command->cmd[0]);
	}
}

int	fork_and_execute(t_mini *shell, t_command *command)
{
	int	is_builtin;

	// debug_print("cmd_i: %d\n", command->cmd_i);
	is_builtin = builtins(command->cmd[0]);
	signal_reset();
	shell->pids[command->cmd_i] = fork();
	if (shell->pids[command->cmd_i] == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (shell->pids[command->cmd_i] == 0)
	{
		// debug_print("Child process %d created (PID: %d)\n", command->cmd_i, getpid());
		close_unused_fds(shell, command->cmd_i);
		if (!resolve_fds(shell, command))
		{
			debug_print("failed to resolve fds\n");
			return (FALSE);
		}
		check_print("After resolving fd's\n");
		check_print("Command nro %d's input_fd: %d\n", command->cmd_i, command->input_fd);
		check_print("Command nro %d's output_fd: %d\n", command->cmd_i, command->output_fd);
		if (!dup_input(shell, command, command->cmd_i))
			debug_print("failed to dup input\n");
		if (!dup_output(shell, command, command->cmd_i))
			debug_print("failed to dup output\n");
		if (builtins(command->cmd[0])) //check for builtin cmd in pipe
			exec_forked_builtin(shell, command, is_builtin);
		else
			// exec_forked_cmd(shell, command, i);
			exec_forked_cmd(shell, command);
	}
	return (TRUE);
}

/* Creates pipes from shell->pipes array. All pipes are created at the same time. */
int	create_pipes(t_mini *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		if (pipe(shell->pipes[i]) == -1)
		{
			perror("pipe failed");
			return (FALSE); // call close open fd's in calling process_commands
		}
		i++;
	}
	return (TRUE);
}

/* Allocates memory for 2D pipe array (int **pipes).*/
static int	allocate_pipes(t_mini *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!shell->pipes)
		return (FALSE);
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipes[i] = ft_calloc(2, sizeof(int)); //2 for fd[0] and fd[1] for each pipe array element
		if (!shell->pipes[i])
		{
			free_pipes(shell, i);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/* Creates and allocates PID array (one PID for each shell->cmd_count).*/
static int	allocate_pids(t_mini *shell)
{
	shell->pids = ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		// free and close everything and exit minishell (malloc failure);
		return (FALSE);
	}
	return (TRUE);
}


/*Calls allocate_pids.
Calls allocate_pipes() and create_pipes() if cmd_count > 1.
Returns to exec_child().*/
int	init_pipeline(t_mini *shell)
{
	if (!allocate_pids(shell))
		return (FALSE);
	if (shell->cmd_count > 1)
	{
		if (!allocate_pipes(shell))
			return (FALSE);
		if (!create_pipes(shell))
		{
			free(shell->pids);
			// close all open fds, free everything, and determine exit code
			return (FALSE);
		}
		// debug_print("cmd count: %d\n", shell->cmd_count);
		// debug_print("pipe read end: %d\n", shell->pipes[0][0]);
		// debug_print("pipe write end: %d\n", shell->pipes[0][1]);
	}
	return (TRUE);
}
