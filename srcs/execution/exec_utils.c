#include "minishell.h"

/*	Loops over shell->cmd_count and waits for all child processes 
	matching pid[i] to die.
	Upon unsuccessful waitpid() call, errno is assigned to shell->exit_code.*/
int	wait_for_children(t_mini *shell)
{
	int		i;
	int		status;
	int		signum;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			shell->exit_code = errno;
		}
		if (WIFEXITED(status))
		{
			if (g_mrworldwide == 1)
				// g_mrworldwide = 1;
				shell->exit_code = 1;
			else
				// g_mrworldwide = WEXITSTATUS(status); //or shell->exit_code?
				shell->exit_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			signum = WTERMSIG(status);
			if (signum == SIGINT)
				// g_mrworldwide = 130;
				shell->exit_code = 130;
		}
		i++;
	}
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
	if (!cmd)
		error_cmd(shell, cmd, "command not found", 127);
	if (access(cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd, '/'))
			error_cmd(shell, cmd, "No such file or directory", 1);
		else
			error_cmd(shell, cmd, "command not found", 127);
	}
	if (is_dir(cmd) == true)
		error_cmd(shell, cmd, "Is a directory", 126);
	if (access(cmd, X_OK) == -1)
		error_cmd(shell, cmd, "Permission denied", 1);
	return (0);
}
