#include "minishell.h"

/*Extracts the commands and tokens from t_command into char **array. */
char	**extract_from_tcmd(t_mini *shell, t_command *command)
{
	t_token	*token;
	int		count;
	int		i;

	if (!command || !command->tokens)
		return (NULL);
	count = count_cmd_args_for_exec(command->tokens);
	shell->cmd = (char **)malloc(sizeof(char *) * (count + 1));
	if (!shell->cmd)
		return (NULL);
	i = 0;
	token = command->tokens;
	while (token)
	{
		if (token->type == CMD)
		{
			shell->cmd[i] = ft_strdup(token->value);
			if (!shell->cmd[i])
				ft_free_array(&shell->cmd);
			i++;
		}
		token = token->next;
	}
	shell->cmd[i] = NULL;
	return (shell->cmd);
}

/*	Loops over shell->cmd_count and waits for all child processes 
	matching pid[i] to die.
	Upon unsuccessful waitpid() call, errno is assigned to shell->exit_code.*/
void	wait_for_children(t_mini *shell)
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
				g_mrworldwide = 1;
			else
				g_mrworldwide = WEXITSTATUS(status); //or shell->exit_code?
		}
		else if (WIFSIGNALED(status))
		{
			signum = WTERMSIG(status);
			if (signum == SIGINT)
				g_mrworldwide = 130;
		}
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
