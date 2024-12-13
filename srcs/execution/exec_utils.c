#include "../../includes/minishell.h"

void	close_all(t_mini *shell, t_command *command)
{
	if (command->input_fd >= 0)
		close(command->input_fd);
	if (command->output_fd >= 0)
		close(command->output_fd);
	close(shell->pipe_fd[0]);
	close(shell->pipe_fd[1]);
}

// void	open_file(t_mini *shell, t_command *command)
// {
// 	if (first_or_second == FIRST)
// 	{
// 		if (open(command->input_fd, O_RDONLY) == -1)
// 			exit_error(shell, command->input_fd);
// 	}
// 	if (first_or_second == SECOND)
// 	{
// 		if (open(command->output_fd, O_CREAT | O_WRONLY | O_TRUNC, 0644) == -1)
// 			exit_error(shell, command->output_fd);
// 	}
// }

// void	dup_close(t_mini *shell, t_command *command)
// {
// 	if (first_or_second == FIRST)
// 	{
// 		if (dup2(command->input_fd, STDIN_FILENO) == -1
// 			|| dup2(shell->pipe_fd[1], STDOUT_FILENO) == -1)
// 			exit_error(shell, "dup2 failed on first child");
// 	}
// 	else if (first_or_second == SECOND)
// 	{
// 		if (dup2(shell->pipe_fd[0], STDIN_FILENO) == -1
// 			|| dup2(command->output_fd, STDOUT_FILENO) == -1)
// 			exit_error(shell, "dup2 failed on second child");
// 	}
// 	close_all(shell, command);
// }

int	wait_for_children(t_mini *shell, pid_t pid)
{
	int		status;

	if (waitpid(pid, &status, 0) == -1)
	{
		shell->exit_code = 1;
		perror("waitpid failed");
	}
	else if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	return (shell->exit_code);
}

bool	is_dir(char *path)
{
    struct stat	sb;

    if (stat(path, &sb) == -1)
        return (false);
    return (S_ISDIR(sb.st_mode));
}

int	check_access(t_mini *shell, char *cmd)
{
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			errno = ENOENT;
		else
			errno = 0;
		return (error_cmd(shell, cmd));
	}
	if (is_dir(cmd) == true)
	{
		errno = EISDIR;
		return (error_cmd(shell, cmd));
	}
	if (access(cmd, X_OK) == -1)
	{	
		errno = EACCES;
		return (error_cmd(shell, cmd));
	}
	return (0);
}
