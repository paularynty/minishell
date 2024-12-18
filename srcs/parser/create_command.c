#include "minishell.h"

static t_command	*init_command(int pipes, int i)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->tokens = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->cmd_count = pipes + 1;
	cmd->cmd_i = i;
	cmd->next = NULL;
	return (cmd);
}

t_command	*create_command(char *cmd_str, int pipes, int i)
{
	t_command	*command;
	char		**args;

	command = init_command(pipes, i);
	if (!command)
		return (NULL);
	args = split_cmd_args(cmd_str);
	// printf("After split_cmd_args\n");
	if (!args || !tokenize_args(command, args))
	{
		free_2d_array(args); // check later if in ft_free_array there's a check to avoid double free
		free(command);
		return (NULL);
	}
    t_token *temp = command->tokens;
    while (temp)
    {
        temp = temp->next;
    }
	if (args)
		free_2d_array(args);
	command->next  = NULL;
	return (command);
}
