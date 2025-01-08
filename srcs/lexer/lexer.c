#include "minishell.h"

char	*add_space(char *input, int end)
{
	char	*new_input;
	int		input_len;
	int		new_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	input_len = ft_strlen(input);
	new_len = input_len + 1;
	new_input = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_input)
		return (NULL);
	while (i < end && input[i])
		new_input[j++] = input[i++];
	new_input[j] = ' ';
	j++;
	while (input[i])
		new_input[j++] = input[i++];
	new_input[j] = '\0';
	return (new_input);
}

char	*add_missing_spaces(char *input)
{
	char	*spaced;
	int		i;

	i = 0;
	spaced = NULL;
	while (input && input[i])
	{
		while (input[i] && char_is_whitespace(input[i]))
			i++;
		while (input[i] && !char_is_whitespace(input[i]))
		{
			if (input[i] == '\'' || input[i] == '"')
			{
				i += quote_offset(input + i, input[i]);
				continue ;
			}
			if (ft_strchr("><", input[i]) && i > 0)
			{
				spaced = add_space(input, i);
				free(input);
				if (!spaced)
					return (NULL);
				input = spaced;
				i += 2;
				if (input[i] == input[i - 1])
					i++;
			}
			if (i > 0 && ft_strchr("><", input[i - 1])
				&& !ft_strchr("><", input[i]))
			{
				spaced = add_space(input, i);
				free(input);
				if (!spaced)
					return (NULL);
				input = spaced;
				i += 2;
				if (input[i] == input[i - 1])
					i++;
			}
			else
				i++;
		}
	}
	return (input);
}

/**
 * Validates the initial user input before parsing.
 *
 * @shell: Pointer to the shell structure.
 * @input: The expanded input string (shell->input).
 *
 * - Checks if the input consists only of whitespace.
 * - Validates that all quotes in the input are properly matched.
 * - Ensures there are no improper backslashes in the input.
 * - Verifies the correctness of input redirection syntax.
 * - Confirms that all pipes are closed and valid.
 * 
 * Returns TRUE if the input is valid, FALSE if any validation fails.
 * */
int	valid_input(t_mini *shell, char *input)
{
	if (str_is_whitespace(input))
		return (FALSE);
	if (!matching_quotes(shell, input))
		return (FALSE);
	if (backslash(shell, input))
		return (FALSE);
	if (!valid_redirection(shell, input))
		return (FALSE);
	if (!closed_pipes(shell, input))
		return (FALSE);
	if (!valid_pipes(shell, input))
		return (FALSE);
	return (TRUE);
}

int	lexer(t_mini *shell, char *line)
{
	shell->input = expand_input(shell, line);
	if (!shell->input)
	{
		ft_putstr_fd("malloc", STDERR_FILENO);
		shell->abort = 1;
		return (FALSE);
	}
	if (!valid_input(shell, shell->input))
		return (FALSE);
	shell->input = add_missing_spaces(shell->input);
	if (!shell->input)
	{
		ft_putstr_fd("malloc", STDERR_FILENO);
		shell->abort = 1;
		return (FALSE);
	}
	return (TRUE);
}
