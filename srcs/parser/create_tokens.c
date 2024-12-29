#include "minishell.h"

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
	}
}

static t_token_type	identify_token_type(char *value)
{
	if (ft_strcmp(value, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(value, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (REDIR_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (HEREDOC);
	return (CMD);
}

static t_token	*create_token(char *arg, char *prev)
{
	t_token	*token;

	token = malloc(sizeof(t_token) + 1);
	if (!token)
		return (NULL);
	token->value = ft_strdup(arg);
	if (!token->value)
	{
		free(token);
		return (NULL); // (malloc failure)
	}
	if (prev && *prev && (ft_strcmp(prev, ">") == 0
		|| ft_strcmp(prev, ">>") == 0 || ft_strcmp(prev, "<") == 0
		|| ft_strcmp(prev, "<<") == 0))

	{
		if (ft_strcmp(prev, "<<") != 0)
			token->type = FILENAME;
		else
			token->type = DELIMITER;
	}
	else
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
		if (i > 0)
			new_token = create_token(args[i], args[i - 1]);
		else
			new_token = create_token(args[i], NULL);
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

