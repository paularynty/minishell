#include "minishell.h"

/*******************************************
 * 
 * handle_heredoc() needs to be implemented
 * 
 *******************************************/

/*******************************************
 * 
 * Our friend Chat sketched up something like this for wait_for_children
 * 
 *******************************************/

// void wait_for_children(pid_t *pids, int cmd_count, t_mini *shell)
// {
// 	int i = 0;
// 	int status;

// 	while (i < cmd_count)
// 	{
// 		if (waitpid(pids[i], &status, 0) == -1)
// 		{
// 			perror("waitpid failed");
// 			shell->exit_code = errno;
// 		}
// 		else if (WIFEXITED(status))
// 		{
// 			shell->exit_code = WEXITSTATUS(status); // Save the last command's exit code
// 		}
// 		i++;
// 	}
// }

/************************************
 * 
 * close_all_pipes() needs to be implemented
 * 
 ************************************/

void	close_unused_pipes(int pipe_fd[][2], int cmd_count, int index)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		if (i != index - 1)
			close(pipe_fd[i][0]);
		if (i != index)
			close(pipe_fd[i][1]);
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
void	handle_child_process(t_command *cmd, t_mini *shell, int pipe_fd[][2], int cmd_count)
{
	char	*cmd_path;

	close_unused_pipes(pipe_fd, cmd_count, cmd->cmd_i);
	//dupping, still unsure of this suggestion:
	if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		// I'm way too confused at this point, at least close fd's here and also in parent, return correct error and exit process?
	if (dup2(cmd->input_fd, STDOUT_FILENO) == -1)
		// I'm way too confused at this point, at least close fd's here and also in parent, return correct error and exit process?
	// close_all_pipes or close_unused_pipes? CONFUSION STRIKES AGAIN
	shell->cmd = prep_command() // it's now static, no time to modify I leave in 5 minutes
	if (!shell->cmd || !(cmd_path = get_cmd_path(shell, shell->cmd[0])))
	{
		// error handlingia tulille
		//exitataan process oikealla return valuella (=exit code)
	}
	execve(cmd_path, shell->cmd, shell->env);
    free(cmd_path); // If execve fails, free allocated resources.
    error_cmd(shell, shell->cmd[0]);
    exit(shell->exit_code);
}

int	handle_input(t_command *cmd, int *error)
{
	t_token	*token;
	int		fd;

	fd = -1;
	token = cmd->tokens;
	while (token)
	{
		if (token->type == REDIRECT_IN)
			fd = open(cmd->token->next->value, O_RDONLY);
	//	else if (token->type == HEREDOC)
		//	fd = handle_heredoc(cmd->token->next->value);
		token = token->next;
	}
	return (fd);
}

int	handle_output(t_command *cmd, int *error)
{
	t_token	*token;
	int		fd;

	token = cmd->tokens;
	while (token)
	{
		if (token->type == REDIRECT_OUT)
		{
			fd = open(cmd->token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				*error = errno;
		}
		else if (tokens->type == REDIRECT_APPEND)
		{
			fd = open(cmd->token->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				*error = errno;
		}
		// if (*error)
		//	strerrorilla error viesti ja exit coodia talteen johonkin? Ei exitata koska ei olla forkattu
		token = token->next;
	}
	return (fd);
}

void	execute_pipeline(t_command *cmd, int pipe_fd[][2], pit_t *pids, t_mini *shell)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (cmd)
	{
		cmd->input_fd = handle_input(cmd, &error);
		cmd->output_fd = handle_output(cmd, &error);
		if (!error)
		{
			setup_fds(cmd, pipe_fd, cmd->cmd_count);
			pids[i] = fork();
			if (pids[i] == 0)
				handle_child_process(cmd, shell, pipe_fd, cmd->cmd_count);
			else if (pids[i] < 0)
				// free and close everything and exit;
		}
		else
			// Save correct exit_code to shell struct and proceed to the next cmd.
		cmd = cmd->next;
		i++;
	}
}

/**********************************************************
 * 
 * All the pipes should be created at the same time t. Noel
 * 
 * ********************************************************/
int		create_pipes(int pipe_fd[][2], int cmd_count)
{
	int	i;
	i = 0;

	while (i < cmd_count - 1)
	{
		if (pipe(pipe_fd[i]) == -1)
			return (FALSE);  // call close open fd's in calling process_commands
		i++;
	}
	return (TRUE)
}

/*****************************************************************
 * 
 * Here we create array of process ID's and call pipe creation and executing pipeline
 *  
 *****************************************************************/

void	process_commands(t_command *cmd, t_mini *shell)
{
	int		pipe_fd[cmd->cmd_count - 1][2];
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * cmd->cmd_count);
	if (!pids)
		// free and close everything and exit minishell (malloc failure);
	if (!create_pipes(pipe_fd, cmd->cmd_count))
	{
		free(pids);
		// close all open fds and free alls and determine exit_code
	}
	execute_pipeline(cmd, pipe_fd, pids, shell);
	close_all_pipes(pipe_fd, cmd);
	//shell->exit_code = wait_for_children() <- needs to be modified to take in pids, cmd, and shell
	free(pids);
	// go back to calling function (minishell) and free necessary stuff
}
