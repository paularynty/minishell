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

void	move_i_past_whitespace(char *input, int *i)
{
	while (input[*i] && char_is_whitespace(input[*i]))
		(*i)++;
}

char	*spaces_to_input(char *input, int *i)
{
	char	*spaced;

	if (!char_is_whitespace(input[*i - 1]) && !(ft_strchr("><", input[*i - 1])
			&& ft_strchr("><", input[*i])))
		spaced = add_space(input, *i);
	else
	{
		(*i)++;
		return (input);
	}
	free(input);
	if (!spaced)
	{
		perror("malloc");
		return (NULL);
	}
	input = spaced;
	*i += 1;
	if (input[*i] == input[*i - 1])
		(*i)++;
	return (input);
}

char	*add_missing_spaces(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		move_i_past_whitespace(input, &i);
		while (input[i] && !char_is_whitespace(input[i]))
		{
			if (char_is_quote(input[i]) && !ft_strchr("><", input[i - 1]))
			{
				i += quote_offset(input + i, input[i]);
				continue ;
			}
			if (i > 0 && (ft_strchr("><", input[i])
					|| ft_strchr("><", input[i - 1])))
			{
				input = spaces_to_input(input, &i);
				if (!input)
					return (NULL);
			}
			else
				i++;
		}
	}
	return (input);
}
