#include "minishell.h"

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
	// printf("After strlen in replace_segment input_len: %d\n", input_len);
	repl_len = ft_strlen(replacement);
	// printf("After strlen in replace_segment repl_len: %d\n", repl_len);
	new_len = input_len - (end - start) + repl_len;
	new_input = (char *)malloc(sizeof(char)* new_len + 1);
	// printf("After malloc in replace_segment input: %s\n", input);
	if (!new_input)
		return (NULL);
	if (ft_strlcpy(new_input, input, start + 1) == 0)
		return (NULL);
	// printf("After 1st strlcpy in replace_segment input: %s\n", input);
	// printf("After 1st strlcpy in replace_segment new_input: %s\n", new_input);
	if (replacement)
		ft_strlcpy(new_input + start, replacement, start + repl_len + 1);
	// printf("After 2nd strlcpy in replace_segment input: %s\n", input);
	// printf("After 2nd strlcpy in replace_segment new_input: %s\n", new_input);
	ft_strlcpy(new_input + start + repl_len, input + end, new_len + 1);
	// printf("After 3rd strlcpy in replace_segment input: %s\n", input);
	// printf("After 3rd strlcpy in replace_segment new_input: %s\n", new_input);
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
	new_input = replace_segment(input, *i, *i + 2, value);
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
		if (input[i] == '$' && input[i + 1] != '$' && !whitespace(input[i + 1]))
		{
			if (input[i + 1] == '?')
				input = expand_exitcode(minish, input, &i);
			else if (input[i + 1] == '"' || input[i + 1] == '\'')
			{
//				printf("We have quotes, input before replace segment: %s\n", input);
				input = replace_segment(input, i, i + 1, NULL);
//				printf("Input after replace segment: %s\n", input);
				if (input[i + 1] == '"')
					i++;
				else
					i += quotes_offset(input + i + 1, input[i + 1]);
//			printf("Input's index after i increase: %s\n", (input + i));
			}
			else
				input = expand_variable(minish, input, &i);
			if (!input)
				return (NULL);
		}
		else if (input[i] == '\'')
			i += quotes_offset(input + i, input[i]);
		else
			i++;
	}
	return (input);
}