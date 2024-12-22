#include "minishell.h"

static char	**prep_command(t_mini *shell, t_command *command)
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
			shell->cmd[i] = strdup(token->value);
			if (!shell->cmd[i])
				ft_free_array(&shell->cmd);
			i++;
		}
		token = token->next;
		check_print("token loop\n");
	}
	shell->cmd[i] = NULL;
	return (shell->cmd);
}

static int	exec_parent(t_mini *shell, int builtin_id)
{
	handle_builtin(builtin_id, shell);
	return (TRUE);
}

//TO DO: up until a pipe, only the first token can be CMD
//the next ones after that (excl. redires etc.) are ARG
//so that executor works as it should
void	execute(t_mini *shell, t_command *command)
{
	int		builtin_id;
	int		i;

	i = 0;
	shell->cmd = prep_command(shell, command);
	builtin_id = builtins(shell->cmd[0]);
	debug_print("%d\n", shell->cmd_count);
	while (i < shell->cmd_count)
	{
		if (shell->cmd_count == 1)
			exec_parent(shell, builtin_id);
		else
			exec_child(shell, command);
		i++;
	}
	ft_free_array(&shell->cmd);
}
