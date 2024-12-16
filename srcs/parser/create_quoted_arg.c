#include "minishell.h"

char	*create_quoted_arg(char *str, int *i, int len)
{
	char	*arg;
	int		j;
	int		k;

	k = 0;
	arg = (char *)malloc(sizeof(char) * len + 1);
	if (!arg)
		return (NULL);
	while (str[*i] && !char_is_whitespace(str[*i]))
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			j = *i;
			(*i)++;
			while (str[*i] && str[*i] != str[j] && !char_is_whitespace(str[*i]))
				arg[k++] = str[(*i)++];
		}
		else
			arg[k++] = str[(*i)++];
		(*i)++;
	}
	arg[k] = '\0';
	return (arg);
}
