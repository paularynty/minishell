/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:26 by prynty            #+#    #+#             */
/*   Updated: 2024/11/28 12:53:31 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

static void	add_command(t_command **head, t_command *new_cmd)
{
	t_command	*temp;

	if (!*head)
		*head = new_cmd;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_cmd;
		// new_cmd->next = NULL; // this might be unnecessary
	}
}

t_command	*tokenizer(const char *input)
{
	char		**cmds;
	t_command	*commands; // is there a need to init as NULL?
	t_command	*current_cmd; // is there a need to init as NULL?
	int			i;

	i = 0;
	cmds = split_by_pipes(input);
	if (!cmds)
		return (NULL);
	while (cmds[i] != NULL)
	{
		current_cmd = create_command(cmds[i]);
		if (!current_cmd)
		{
			ft_free_array(cmds);
			free_commands(commands);
			return (NULL);
		}
		add_command(&commands, current_cmd); // adds another cmd to the linked list
		i++;
	}
	ft_free_array(cmds);
	return (commands);
}
