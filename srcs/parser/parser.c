#include "minishell.h"

static void	add_command(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*temp;

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

/*Splits input by pipes into command chunks.
Adds command chunks to linked list.*/
t_cmd	*tokenizer(t_mini *shell, const char *input)
{
	char		**cmds;
	t_cmd	*commands;
	t_cmd	*current_cmd;
	int			i;

	i = 0;
	commands = NULL;
	cmds = split_by_pipes(input);
	if (!cmds)
		return (NULL);
	while (cmds[i] != NULL)
	{
		current_cmd = create_command(cmds[i], i);
		if (!current_cmd)
		{
			free_2d_array(cmds);
			free_commands(commands);
			return (NULL);
		}
		add_command(&commands, current_cmd);
		shell->cmd_count++;
		i++;
	}
	free_2d_array(cmds);
	return (commands);
}
