#include "minishell.h"

char	*create_quoted_arg(char *str, int *i, int len, int k)
{
	char	*arg;
	int		j;

	arg = (char *)malloc(sizeof(char) * len + 1);
	if (!arg)
		return (NULL);
	while (str[*i] && char_is_whitespace(str[*i]))
		(*i)++;
	while (str[*i] && !char_is_whitespace(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			j = *i;
			(*i)++;
			while (str[*i] && str[*i] != str[j])
				arg[k++] = str[(*i)++];
			if (str[*i] == str[j])
				(*i)++;
		}
		else
			arg[k++] = str[(*i)++];
	}
	arg[k] = '\0';
	return (arg);
}
