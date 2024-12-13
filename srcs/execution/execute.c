#include "../../includes/minishell.h"

static char	**get_env_path(char **env)
{
	char	**env_path;

	while (*env && !ft_strnstr(*env, "PATH=", 5))
		env++;
	if (!*env)
	{
		errno = ENOENT;
		return (NULL);
	}
	env_path = ft_split(*env + 5, ':');
	if (!env_path)
		return (NULL);
	return (env_path);
}

static char	*get_full_path(char **env_path, char *cmd)
{
	char	*temp_path;
	char	*full_path;

	while (*env_path)
	{
		temp_path = ft_strjoin(*env_path, "/");
		if (!temp_path)
			return (NULL);
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		env_path++;
	}
	return (NULL);
}

static char	*get_cmd_path(t_mini *shell, char *cmd)
{
	char	*cmd_path;
	char	**env_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		else
		{
			errno = ENOENT;
			error_cmd(shell, cmd);
		}
	}
	env_path = get_env_path(shell->env);
	if (!env_path)
		return (NULL);
	cmd_path = get_full_path(env_path, cmd);
	ft_free_array(&env_path);
	return (cmd_path);
}

// static int	prep_command(t_mini *shell, char *line)
// {
// 	shell->cmd = ft_split(line, ' ');
// 	if (!shell->cmd || !shell->cmd[0])
// 		return (error_cmd(shell, shell->cmd[0]));
// 	return (0);
// }

static int count_cmd_args(t_token *tokens)
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

static char	**prep_command(t_mini *shell, t_command *command)
{
	t_token	*token;
	int		count;
	int		i;

	if (!command || !command->tokens)
		return (NULL);
	count = count_cmd_args(command->tokens);
	shell->cmd = (char **)malloc(sizeof(char *) * (count + 1));
	if (!shell->cmd)
		return (NULL);
	i = 0;
	token = command->tokens;
	while (token)
	{
		if (token->type == CMD)
		{
			shell->cmd[i] = strdup(token->value);
			if (!shell->cmd[i])
				ft_free_array(&shell->cmd);
			i++;
		}
		token = token->next;
	}
	shell->cmd[i] = NULL;
	return (shell->cmd);
}

int	exec_fork(t_mini *shell)
{
	char		*cmd_path;
	pid_t		pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		cmd_path = get_cmd_path(shell, shell->cmd[0]);
		if (!cmd_path)
			check_access(shell, shell->cmd[0]);
		check_access(shell, cmd_path);
		execve(cmd_path, shell->cmd, shell->env);
		free(cmd_path);
		exit(error_cmd(shell, shell->cmd[0]));
	}
	return (wait_for_children(shell, pid));
}

void	execute(t_mini *shell, t_command *command)
{
	int	builtin_id;

	shell->cmd = prep_command(shell, command);
	builtin_id = builtins(shell->cmd[0]);
	if (builtin_id) // 0 = BUILTIN_NONE, everything else is builtin
		handle_builtin(builtin_id, shell);
	else
		exec_fork(shell);
	ft_free_array(&shell->cmd);
}
