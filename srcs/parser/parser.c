#include "../../includes/minishell.h"

static void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*temp;

	temp = NULL;
	// printf("Adding command: %p\n", new_cmd);
	// printf("command->next before traversal: %p\n", new_cmd->next);
	if (!*head)
	{
		printf("New head command: %p\n", new_cmd);
		*head = new_cmd;
	}
	else
	{
		temp = *head;
		while (temp->next)
		{
			printf("Traversing command: %p\n", temp);
			temp = temp->next;
		}
		printf("Appending to command: %p\n", temp);
		temp->next = new_cmd;
	}
	printf("command->next after adding: %p\n", new_cmd->next);
}

t_command	*tokenizer(const char *input)
{
	char		**cmds;
	t_command	*commands;
	t_command	*current_cmd;
	int			i;

	i = 0;
	commands = NULL;
	current_cmd = NULL;
	cmds = split_by_pipes(input);
	if (!cmds)
		return (NULL);
	while (cmds[i] != NULL)
	{
		current_cmd = create_command(cmds[i]);
		if (!current_cmd)
		{
			free_2d_array(cmds);
			free_commands(commands);
			return (NULL);
		}
		add_command(&commands, current_cmd); // adds another cmd to the linked list
		i++;
	}
	free_2d_array(cmds);
	return (commands);
}
