#include "minishell.h"

// /*Extracts the commands and tokens from t_command into char **array. */
// static char	**extract_singular_command(t_command *command)
// {
// 	t_token	*token;
// 	char	**cmd;
// 	int		count;
// 	int		i;

// 	if (!command || !command->tokens)
// 		return (NULL);
// 	count = count_cmd_args_for_exec(command->tokens);
// 	cmd = (char **)malloc(sizeof(char *) * (count + 1));
// 	if (!cmd)
// 		return (NULL);
// 	i = 0;
// 	token = command->tokens;
// 	while (token)
// 	{
// 		if (token->type == CMD)
// 		{
// 			cmd[i] = ft_strdup(token->value);
// 			if (!cmd[i])
// 				ft_free_array(&cmd);
// 			i++;
// 		}
// 		token = token->next;
// 	}
// 	cmd[i] = NULL;
// 	return (cmd);
// }

// char	***extract_all_commands(t_mini *shell, t_command *commands)
// {
// 	t_command	*temp;
// 	char		***cmds;
// 	int			i;

// 	cmds = (char ***)malloc(sizeof(char **) * (shell->cmd_count + 1));
// 	if (!cmds)
// 		return (NULL);
// 	temp = commands;
// 	i = 0;
// 	while (temp)
// 	{
// 		cmds[i] = extract_singular_command(temp);
// 		if (!cmds[i])
// 		{
// 			while (i > 0)
// 				ft_free_array(&cmds[--i]);
// 			free(cmds);
// 			return (NULL);
// 		}
// 		i++;
// 		temp = temp->next;
// 	}
// 	cmds[i] = NULL;
// 	return (cmds);
// }

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
