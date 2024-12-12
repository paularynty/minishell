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
			exp_var = (char *)malloc(sizeof(char) * env_len + 1);
		//	if (!exp_var)
		// print malloc fail message and do something
			exp_var = ft_substr(minish->env[i], key_len + 1, env_len + 1);
		//	if (!exp_var)
		//	print malloc fail message and do something
			return (exp_var);
		}
		i++;
	}
	return (NULL);
}

char	*replace_segment(char *input, int start, int end, char *replacement)
{
	char	*new_input;
	int		input_len;
	int		repl_len;
	int		new_len;

	input_len = ft_strlen(input);
	if (replacement)
		repl_len = ft_strlen(repl_len);
	new_len = input_len - (end - start) + repl_len;
	new_input = (char *)malloc(sizeof(char)* new_len + 1);
	if (!new_input)
		return (NULL);
	if (ft_strlcpy(new_input, input, start + 1) == 0)
		return (NULL);
	if (replacement)
	{
		if (ft_strlcpy(new_input + start, replacement, start + repl_len + 1) == 0)
			return (NULL);
	}
	if (ft_strlcpy(new_input + start + repl_len, input + end, new_len + 1) == 0)
		return (NULL);
	reteurn (new_input);
}

char	*expand_input(t_mini *minish, char *input)
{
	int		end;
	int		i;
	char	*key;
	char	*value;
	char	*expanded;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			end = i + 1; // skipping '$' character
			while (input[end] && !iswhitespace(input[end]))
				end++;
			if (end > i + 1)
			{	
				key = ft_substr(input, i + 1, end - (i + 1));
			//	if (!key)
			//		handle malloc fail
				value = get_variable(minish, key, end - i + 1);
				free(key);
				if (value)
				{
					expanded = replace_segment(input, i, end, value);
					i += ft_strlen(value);
					free(value);
				}
				else
					expanded = replace_segment(input, i, end, NULL);
			}
			else
				i++;
		}
		else if (input[i] == '"' || input[i] == '\'')
			i += quotes_offset(input + i, input[i])
		else
			i++;
	}
	return (expanded);
}

int lexer(t_mini *minish, char *line)
{
	if (!valid_input(minish, line))
		return (FALSE);
	minish->input = expand_input(minish, line); // we'll save the expanded input into the struct
	if (!minish->input) // if we ended up with an empty line after "expansion"
		minish->input = ft_strdup("");
//	if (!minish->input) // malloc fail
//		implement malloc fail message and decide how to continue		
	return (TRUE);
}
