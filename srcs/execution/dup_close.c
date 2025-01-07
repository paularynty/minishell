#include "minishell.h"

// void	open_file(t_mini *shell, t_cmd *cmd)
// {
// 	if (first_or_second == FIRST)
// 	{
// 		if (open(cmd->input_fd, O_RDONLY) == -1)
// 			exit_error(shell, cmd->input_fd);
// 	}
// 	if (first_or_second == SECOND)
// 	{
// 		if (open(cmd->output_fd, O_CREAT | O_WRONLY | O_TRUNC, 0644) == -1)
// 			exit_error(shell, cmd->output_fd);
// 	}
// }

// void	dup_close(t_mini *shell, t_cmd *cmd)
// {
// 	if (first_or_second == FIRST)
// 	{
// 		if (dup2(cmd->input_fd, STDIN_FILENO) == -1
// 			|| dup2(shell->pipe_fd[1], STDOUT_FILENO) == -1)
// 			exit_error(shell, "dup2 failed on first child");
// 	}
// 	else if (first_or_second == SECOND)
// 	{
// 		if (dup2(shell->pipe_fd[0], STDIN_FILENO) == -1
// 			|| dup2(cmd->output_fd, STDOUT_FILENO) == -1)
// 			exit_error(shell, "dup2 failed on second child");
// 	}
// 	close_all(shell, cmd);
// }

int	resolve_fds(t_mini *shell, t_cmd *cmd)
{
	// check_print("calling process_redir from resolve_fd's\n");
	if (!process_redir(shell, cmd))
		return (FALSE);
	if (cmd->input_fd == -1)
		cmd->input_fd = STDIN_FILENO;
	if (cmd->output_fd == -1)
		cmd->output_fd = STDOUT_FILENO;
	return (TRUE);
}

int	dup_input(t_mini *shell, t_cmd *cmd, int i)
{
	if (cmd->input_fd != STDIN_FILENO)
	{
		if (!dup2_close(cmd->input_fd, STDIN_FILENO))
		{
			perror("dup2 failed for input redirection");
			shell->exit_code = 1;
			return (FALSE);
		}
		if (i > 0)
			close(shell->pipes[i - 1][0]);
	}
	else if (i > 0)
	{
		if (!dup2_close(shell->pipes[i - 1][0], STDIN_FILENO))
		{
			perror("dup2 failed for pipe input");
			shell->exit_code = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

// Duplicates output to fd if there is a redirection or to write end of pipe
// Redirection takes precedence over pipe
int	dup_output(t_mini *shell, t_cmd *cmd, int i)
{
	if (cmd->output_fd != STDOUT_FILENO)
	{
		if (!dup2_close(cmd->output_fd, STDOUT_FILENO))
		{
			perror("dup2 failed for output redirection");
			shell->exit_code = 1;
			return (FALSE);
		}
		if (i < shell->cmd_count - 1)
			close(shell->pipes[i][1]);
	}
	else if (i < shell->cmd_count - 1)
	{
		if (!dup2_close(shell->pipes[i][1], STDOUT_FILENO))
		{
			perror("dup2 failed for pipe output");
			shell->exit_code = 1;
			return (FALSE);
		}
	}
	return (TRUE);
}

/*Duplicates old_fd to new_fd and closes old_fd.*/
int	dup2_close(int old_fd, int new_fd)
{
	if (old_fd < 0)
	{
		ft_putstr_fd("minishell: invalid file descriptor\n", 2);
		return (FALSE);
	}
	if (dup2(old_fd, new_fd) == -1)
	{
		close(old_fd);
		return (FALSE);
	}
	close(old_fd);
	return (TRUE);
}