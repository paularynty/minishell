#include "minishell.h"

char	*double_quotes_expand(t_mini *shell, char *input, int i)
{
	(i)++;
	while (input[i] && input[i] != '"')
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				input = expand_exit_code(shell, input, &i);
				if (!input)
					return (NULL);
			}
			else if (!char_is_whitespace(input[i + 1])
				&& input[i + 1] != '"')
			{
				input = expand_variable(shell, input, &i);
				if (!input)
					return (NULL);
			}
		}
		else
			i++;
		i++;
	}
	return (input);
}

char	*handle_quotes(t_mini *shell, char *input, int *i)
{
	if (input[*i] == '"')
	{
		input = double_quotes_expand(shell, input, *i);
		if (!input)
			return (NULL);
		*i += quote_offset(input + *i, input[*i]);
	}
	else if (input[*i] == '\'')
		*i += quote_offset(input + *i, input[*i]);
	return (input);
}
