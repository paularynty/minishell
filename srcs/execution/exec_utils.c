#include "minishell.h"

/*	Loops over shell->cmd_count and waits for all child processes 
	matching pid[i] to die.
	Upon unsuccessful waitpid() call, errno is assigned to shell->exit_code.*/
void	wait_for_children(t_mini *shell)
{
	int		status;
	int		i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (waitpid(shell->pids[i], &status, 0) == -1)
		{
			perror("waitpid failed");
			shell->exit_code = errno;
		}
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		i++;
	}
}

int count_cmd_args_for_exec(t_token *tokens)
{
    int count;

	count = 0;
    while (tokens)
    {
        if (tokens->type == CMD)
            count++;
        tokens = tokens->next;
    }
    return (count);
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
