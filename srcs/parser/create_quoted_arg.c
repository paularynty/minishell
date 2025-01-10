#include "minishell.h"
// NEEDS TO BE EDITED OR SPLIT INTO TWO FUNCTIONS

char	*create_quoted_arg(char *str, int *i, int len)
{
	char	*arg;
	int		j;
	int		k;

	k = 0;
	arg = (char *)malloc(sizeof(char) * len + 1);
	if (!arg)
		return (NULL);
	while (str[*i] && char_is_whitespace(str[*i]))
		(*i)++;
	while (str[*i] && len && !char_is_whitespace(str[*i]))
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
