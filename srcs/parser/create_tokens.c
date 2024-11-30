/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:36:24 by sniemela          #+#    #+#             */
/*   Updated: 2024/11/30 15:42:48 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
		// new_token->next = NULL;
	}
}

static t_token_type	identify_token_type(char *value)
{
	if (strcmp(value, "<") == 0)
		return (REDIRECT_IN);
	if (strcmp(value, ">") == 0)
		return (REDIRECT_OUT);
	if (strcmp(value, ">>") == 0)
		return (REDIRECT_APPEND);
	if (strcmp(value, "<<") == 0)
		return (HEREDOC);
	return (CMD);
}

static t_token	*create_token(char *arg)
{
	t_token	*token;

	token = malloc(sizeof(t_token) + 1);
	if (!token)
		return (NULL);
	token->value = ft_strdup(arg);
	if (!token->value)
	{
		free(token);
		return (NULL); // printf descriptive error message (strerror)
	}
	token->type = identify_token_type(token->value);
	token->next = NULL;
	return (token);
}

int		tokenize_args(t_command *command, char **args)
{
	int		i;
	t_token	*new_token;

	i = 0;
	while (args[i])
	{
		new_token = create_token(args[i]);
		if (!new_token)
			return (FALSE);
		// if (new_token->type == HEREDOC) we will see about this later...
		// {
		// 	if (!handle_heredoc(command, args[++i])) ???
		// 		return (FALSE);
		// }
		else
			add_token(&(command->tokens), new_token);
		i++;
	}
	return (TRUE);
}

