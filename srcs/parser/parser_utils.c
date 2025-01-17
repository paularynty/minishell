#include "minishell.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

int	count_token_type(t_token *tokens, enum e_token_type type)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == type)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	quote_offset(const char *input, char quote)
{
	int	offset;

	offset = 1;
	while (input[offset] && input[offset] != quote)
		offset++;
	offset++;
	return (offset);
}

int	count_pipes(const char *input)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quote_offset(input + i, input[i]);
		else if (input[i] == '|')
		{
			pipes++;
			i++;
		}
		else
			i++;
	}
	return (pipes);
}

