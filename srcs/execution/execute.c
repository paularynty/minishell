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
			shell->cmd[i] = ft_strdup(token->value);
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

static int	exec_parent(t_mini *shell, int is_builtin)
{
	handle_builtin(is_builtin, shell);
	return (TRUE);
}

//TO DO: up until a pipe, only the first token can be CMD
//the next ones after that (excl. redires etc.) are ARG
//so that executor works as it should
int	execute(t_mini *shell, t_command *command)
{
	int		is_builtin;
	int		i;

	i = 0;
	shell->cmd = prep_command(shell, command);
	is_builtin = builtins(shell->cmd[0]);
	if (shell->cmd_count == 1 && is_builtin)
		exec_parent(shell, is_builtin);
	else
		exec_child(shell, command);
	ft_free_array(&shell->cmd);
	return (shell->exit_code);
}
