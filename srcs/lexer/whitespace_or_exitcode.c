#include "minishell.h"

char	*expand_exit_code(t_mini *shell, char *input, int *i)
{
	char	*value;
	char	*new_input;

	value = ft_itoa(shell->exit_code);
	if (!value)
		return (NULL);
	new_input = replace_segment(input, *i, *i + 2, value);
	free(input);
	if (!new_input)
		return (NULL);
	*i += ft_strlen(value) - 1;
	free(value);
	return (new_input);
}

char	*wp_or_exit_code(t_mini *shell, char *input, int *i)
{
	if (char_is_whitespace(input[*i + 1]))
	{
		(*i)++;
		return (input);
	}
	else if (input[*i + 1] == '?')
		input = expand_exit_code(shell, input, &(*i));
	return (input);
}
