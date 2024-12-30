#include "minishell.h"

// This is the first argument validation check.
// We check whether the prompt is empty/whitespace, contains uneven quotes or other errors we can handle immediately
// without taking into account pipes. Upon occuring, we send correct error message, update add_history and return matching exit code.
// Add exit_code / error message handling later.

int 	valid_input(char *input)
{
	if (str_is_whitespace(input))
		return (FALSE); // handle whitespace separately? To an exit_function which frees any allocated memory, in bash history is added, rl_on_newline()
	if (!matching_quotes(input))
		return (FALSE);
	if (backslash(input))
		return (FALSE);
	if (!valid_redirection(input))
		return (FALSE);
	if (!closed_pipes(input))
		return (FALSE);
	if (!valid_pipes(input))
		return (FALSE);
	return (TRUE);
}

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
				i += quotes_offset(input + i, input[i]);
			if (ft_strchr("><", input[i]) && i > 0)
			{
				spaced = add_space(input, i);
				// printf("spaced input: %s\n", spaced);
				free(input);
				if (!spaced)
					return (NULL);
				input = spaced;
				i += 2;
				if (input[i] == input[i - 1])
					i++;
			}
			else if ((input[i - 1] == '<' || input[i - 1] == '>') && !ft_strchr("><", input[i]))
			{
				spaced = add_space(input, i);
				// printf("spaced input: %s\n", spaced);
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

int 	lexer(t_mini *shell, char *line)
{
	shell->input = expand_input(shell, line);
	if (!shell->input) // if there was a malloc fail
	{
		check_print("\nWE DON'T HAVE AN INPUT\n");
		return (FALSE);
	}
	if (!valid_input(shell->input))
	{
		free(shell->input);
		return (FALSE);
	}
	check_print("\nafted valid_input: %s\n", line);
	shell->input = add_missing_spaces(shell->input);
	if (!shell->input) // if there was a malloc fail
	{
		check_print("\nWE DON'T HAVE AN INPUT\n");
		return (FALSE);
	}
	check_print("expanded and spaced input: %s\n", shell->input);
	return (TRUE);
}
