#include "minishell.h"

static t_command	*init_command(int i)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->tokens = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->cmd_i = i;
	cmd->next = NULL;
	return (cmd);
}

/*Extracts the CMD token type commands into cmd->args 2D array. */
static char	**extract_command(t_command *command)
{
	t_token	*token;
	char	**cmd;
	int		count;
	int		i;

	if (!command || !command->tokens)
		return (NULL);
	count = count_token_type(command->tokens, CMD);
	cmd = (char **)malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	token = command->tokens;
	while (token)
	{
		if (token->type == CMD)
		{
			cmd[i] = ft_strdup(token->value);
			if (!cmd[i])
				ft_free_array(&cmd);
			i++;
		}
		token = token->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_command	*create_command(char *cmd_str, int i)
{
	t_command	*command;
	char		**args;

	command = init_command(i);
	if (!command)
		return (NULL);
	args = split_cmd_args(cmd_str);
	if (!args)
		return (NULL);
	if (!tokenize_args(command, args))
	{
		free_2d_array(args);
		free(command);
		return (NULL);
	}
	command->cmd = extract_command(command);
	if (!command->cmd)
	{
		free(command);
		free_2d_array(args);
		return (NULL);
	}
	free_2d_array(args);
	command->next = NULL;
	return (command);
}
