#include "minishell.h"

// This is the first argument validation check.
// We check whether the prompt is empty/whitespace, contains uneven quotes or other errors we can handle immediately
// without taking into account pipes. Upon occuring, we send correct error message, update add_history and return matching exit code.
// Add exit_code / error message handling later.

int valid_input(char *input)
{
	if (iswhitespace(input))
		return (FALSE); // handle whitespace separately? To an exit_function which frees any allocated memory, in bash history is added, rl_on_newline()
	if (!matching_quotes(input))
		return (FALSE);
	if (!valid_redirection(input))
		return (FALSE);
	if (!valid_pipes(input))
		return (FALSE);
	if (!closed_pipes(input))
		return (FALSE);
	return (TRUE);
}
char	*get_variable(t_mini *minish, char *key, int key_len)
{
	int		i;
	int		env_len;
	char	*exp_var;

	i = 0;
	exp_var = NULL;
	while (minish->env[i])
	{
		if (ft_strncmp(minish->env[i], key, key_len) == 0 && *(minish->env[i] + key_len) == '=')
		{
			env_len = ft_strlen(minish->env[i] + key_len + 1);
			exp_var = ft_substr(minish->env[i], key_len + 1, env_len);
			if (!exp_var)
				return (NULL);
			return (exp_var);
		}
		i++;
	}
	exp_var = ft_strdup("");
	if (!exp_var)
		return (NULL);
	return (exp_var);
}

char	*replace_segment(char *input, int start, int end, char *replacement)
{
	char	*new_input;
	int		input_len;
	int		repl_len;
	int		new_len;

	input_len = ft_strlen(input);
	repl_len = ft_strlen(replacement);
	new_len = input_len - (end - start) + repl_len;
	new_input = (char *)malloc(sizeof(char)* new_len + 1);
	if (!new_input)
		return (NULL);
	if (ft_strlcpy(new_input, input, start + 1) == 0)
		return (NULL);
	if (replacement)
		ft_strlcpy(new_input + start, replacement, start + repl_len + 1);
	ft_strlcpy(new_input + start + repl_len, input + end, new_len + 1);
	return (new_input);
}

char	*expand_variable(t_mini *minish, char *input, int *i)
{
	int		end;
	char	*key;
	char	*value;
	char	*new_input;

	end = *i + 1;
	while (input[end] && !whitespace(input[end]) && input[end] != '"' && input[end] != '\'')
		end++;
	if (end <= *i + 1)
		return (input);
	key = ft_substr(input, *i + 1, end - *i - 1);
	if (!key)
		return (NULL);
	value = get_variable(minish, key, ft_strlen(key));
	free(key);
	if (!value)
		return (NULL);
	new_input = replace_segment(input, *i, end, value);
	free(input);
	if (!new_input)
		return (NULL);
	*i += ft_strlen(value);
	free(value);
	return (new_input);
}

char	*expand_exitcode(t_mini *minish, char *input, int *i)
{
	char	*value;
	char	*new_input;

	value = ft_itoa(minish->exit_code);
	if (!value)
		return (NULL);
	new_input = replace_segment(input, *i, *i + 1, value);
	free(input);
	if (!new_input)
		return (NULL);
	*i += ft_strlen(value);
	free(value);
	return (new_input);
}

char	*expand_input(t_mini *minish, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				input = expand_exitcode(minish, input, &i);
			else if (input[i + 1] != '$' && input[i + 1] != '"' && input[i + 1] != '\'')
				input = expand_variable(minish, input, &i);
			if (!input)
				return (NULL);
		}
		else if (input[i] == '"' || input[i] == '\'')
			i += quotes_offset(input + i, input[i]);
		else
			i++;
	}
	return (input);
}

int lexer(t_mini *minish, char *line)
{
	if (!valid_input(line))
		return (FALSE);
//	printf("\nafted valid_input: %s\n", line);
	minish->input = expand_input(minish, line);
	if (!minish->input) // if there was a malloc fail
		printf("\nWE DON'T HAVE AN INPUT\n");
	return (TRUE);
}
