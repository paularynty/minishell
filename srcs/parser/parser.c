#include "minishell.h"

static void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*temp;

	temp = NULL;
	if (!*head)
		*head = new_cmd;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

t_command	*tokenizer(const char *input)
{
	char		**cmds;
	t_command	*commands;
	t_command	*current_cmd;
	int			i;
	int			pipes;

	i = 0;
	commands = NULL;
	current_cmd = NULL;
	cmds = split_by_pipes(input, &pipes);
	if (!cmds)
		return (NULL);
	while (cmds[i] != NULL)
	{
		current_cmd = create_command(cmds[i], pipes, i);
		// printf("cmd_i %d\n", current_cmd->cmd_i);
		// printf("cmd_count %d\n", current_cmd->cmd_count);
		if (!current_cmd)
		{
			free_2d_array(cmds);
			free_commands(commands);
			return (NULL);
		}
		add_command(&commands, current_cmd); // adds another cmd to the linked list
		// printf("Command added\n");
		i++;
	}
	free_2d_array(cmds);
	return (commands);
}
