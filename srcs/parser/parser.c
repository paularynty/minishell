/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:26 by prynty            #+#    #+#             */
/*   Updated: 2024/11/30 15:34:31 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

static void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*temp;

	temp = NULL;
	printf("Adding command: %p\n", new_cmd);
	printf("command->next before traversal: %p\n", new_cmd->next);
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
	t_command	*commands; // is there a need to init as NULL?
	t_command	*current_cmd; // is there a need to init as NULL?
	int			i;

	i = 0;
	commands = NULL;
	cmds = split_by_pipes(input);
	if (!cmds)
		return (NULL);
// DEBUGGAUSTA VARTEN:
	int k = 0;
	printf("split by pipes j'lkeen: \n");
	while (cmds[k] != NULL)
	{
		printf("cmd %d: |%s|\n", k+1, cmds[k]);
		k++;
	}
//endif
	while (cmds[i] != NULL)
	{
		printf("ennen create_command\n");
		current_cmd = create_command(cmds[i]);
		printf("create_commandin jalkeen\n");
		if (!current_cmd)
		{
			printf("current_commandin  luominen  epaonnistu\n");
			ft_free_array(&cmds);
			free_commands(commands);
			return (NULL);
		}
		add_command(&commands, current_cmd); // adds another cmd to the linked list
		printf("add commandin luominen onnistu\n");
		i++;
	}
	ft_free_array(&cmds);
	return (commands);
}
