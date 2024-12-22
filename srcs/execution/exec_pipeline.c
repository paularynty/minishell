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

// static void	close_unused_pipes(int pipe_fd[][2], int cmd_count, int index)
// {
// 	int	i;

// 	i = 0;
// 	while (i < cmd_count - 1)
// 	{
// 		if (i != index - 1)
// 			close(pipe_fd[i][0]);
// 		if (i != index)
// 			close(pipe_fd[i][1]);
// 		i++;
// 	}
// }

/* Closes all pipes. (Should also set to -1?) */
static void	close_all_pipes(t_mini *shell, int i)
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

/***********************************************************
 * 
 * 
 * This is Chat GPT inspired, but I think dupping should involve pipe_fds,
 * and also take into account the cmd_count. If cmd_count = 1 and the cmd == builtin, no need to even
 * be in the child process? Also input and output depends on the commands index.
 * 
 * 
 ***********************************************************/
// void	handle_child_process(t_command *cmd, t_mini *shell, int pipe_fd[][2], int cmd_count)
// {
// 	char	*cmd_path;

// 	close_unused_pipes(pipe_fd, cmd_count, cmd->cmd_i);
// 	//dupping, still unsure of this suggestion:
// 	if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
// 		// I'm way too confused at this point, at least close fd's here and also in parent, return correct error and exit process?
// 	if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
// 		// I'm way too confused at this point, at least close fd's here and also in parent, return correct error and exit process?
// 	// close_all_pipes or close_unused_pipes? CONFUSION STRIKES AGAIN
// 	// shell->cmd = prep_command(); // it's now static, no time to modify I leave in 5 minutes
// 	if (!shell->cmd || !(cmd_path = get_cmd_path(shell, shell->cmd[0])))
// 	{
// 		// error handlingia tulille
// 		//exitataan process oikealla return valuella (=exit code)
// 	}
// 	execve(cmd_path, shell->cmd, shell->env);
//     free(cmd_path); // If execve fails, free allocated resources.
//     error_cmd(shell, shell->cmd[0]);
//     exit(shell->exit_code);
// }

// void	execute_pipeline(t_mini *shell, t_command *cmd, int pipe_fd[][2], pid_t *pids)
// {
// 	int	i;
// 	int	error;

// 	i = 0;
// 	error = 0;
// 	while (cmd)
// 	{
// 		cmd->input_fd = handle_input(cmd, &error);
// 		cmd->output_fd = handle_output(cmd, &error);
// 		if (!error)
// 		{
// 			setup_fds(cmd, pipe_fd, cmd->cmd_count);
// 			pids[i] = fork();
// 			if (pids[i] == 0)
// 				handle_child_process(cmd, shell, pipe_fd, cmd->cmd_count);
// 			else if (pids[i] < 0)
// 				shell->abort = 1;
// 				// free and close everything and exit;
// 		}
// 		else
// 			// Save correct exit_code to shell struct and proceed to the next cmd.
// 		cmd = cmd->next;
// 		i++;
// 	}
// }

static void	exec_forked_builtin(t_mini *shell, int is_builtin)
{
	handle_builtin(is_builtin, shell); //rework this to take in account failed builtin exec
	// cleanup_success(shell);
	exit(EXIT_SUCCESS);
}

/* Executes command in child process. 
Upon successful execve() call, exits with EXIT_SUCCESS (0). 
Otherwise cleans everything and exits with predetermined exit code.*/
static void	exec_forked_cmd(t_mini *shell)
{
	char	*cmd_path;
	
	cmd_path = get_cmd_path(shell, shell->cmd[0]);
	if (!cmd_path)
		check_access(shell, shell->cmd[0]);
	check_access(shell, cmd_path);
	signal_reset();
	debug_print("Current input_fd: %d\n", command->input_fd);
	debug_print("Current output_fd: %d\n", command->output_fd);
	debug_print("Current read pipe fd: %d\n", shell->pipes[i][0]);
	debug_print("Current write pipe fd: %d\n", shell->pipes[i][1]);
	if (execve(cmd_path, shell->cmd, shell->env) == -1)
	{
		free(cmd_path);
		error_cmd(shell, shell->cmd[0]);
	}
	debug_print("We go here after execve returns\n");
	exit(EXIT_SUCCESS);
}

static int	fork_and_execute(t_mini *shell, t_command *command, int i)
{
	int	is_builtin;

	is_builtin = builtins(shell->cmd[0]);
	signal_reset();
	shell->pids[i] = fork();
	if (shell->pids[i] == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (shell->pids[i] == 0)
	{
		close_unused_fds(shell, i);
		if (!resolve_fds(shell, command))
			debug_print("failed to dup input\n");
		if (!dup_input(shell, command, i))
			debug_print("failed to dup input\n");
		if (!dup_output(shell, command, i))
			debug_print("failed to dup output\n");
		if (builtins(shell->cmd[0])) //check for builtin cmd in pipe
			exec_forked_builtin(shell, is_builtin);
		else
			exec_forked_cmd(shell);
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

static int	allocate_pipes(t_mini *shell)
{
	int	i;

	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!shell->pipes)
	{
		shell->abort = 1;
		return (FALSE);
	}
	i = 0;
	while (i < shell->cmd_count - 1)
	{
		shell->pipes[i] = ft_calloc(2, sizeof(int)); //2 for fd[0] and fd[1] for each pipe array element
		if (!shell->pipes[i])
		{
			free_pipes(shell, i);
			shell->abort = 1;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

/* Creates and allocates PID array (one PID for each shell->cmd_count).
Creates pipes, and executes pipeline.*/
static int	init_pipeline(t_mini *shell)
{
	shell->pids = ft_calloc(shell->cmd_count, sizeof(pid_t));
	if (!shell->pids)
	{
		// free and close everything and exit minishell (malloc failure);
		shell->abort = 1;
		return (FALSE);
	}
	if (shell->cmd_count > 1)
	{
		if (!allocate_pipes(shell))
			return (FALSE);
	}
	return (TRUE);
}

int	exec_child(t_mini *shell, t_command *command)
{
	int	i;

	i = 0;
	if (!init_pipeline(shell))
		return (FALSE);
	if (!create_pipes(shell))
	{
		free(shell->pids);
		close_all_pipes(shell, i); //modify to suit 2d pipe array better
		// close all open fds, free everything, and determine exit code
		return (FALSE);
	}
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
