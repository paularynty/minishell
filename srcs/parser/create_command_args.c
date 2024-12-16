#include "minishell.h"

static int	count_cmd_args(char *cmd_str)
{
	int	i;
	int	args;

	i = 0;
	args = 0;
	while (cmd_str[i])
	{
		while (cmd_str[i] && char_is_whitespace(cmd_str[i]))
			i++;
		if (!cmd_str[i])
			break ;
		args++;
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
			i += quotes_offset(cmd_str + i, cmd_str[i]);
		while (cmd_str[i] && cmd_str[i] != '"' && cmd_str[i] != '\''
			&& !char_is_whitespace(cmd_str[i]))
			i++;
	}
	return (args);
}

static char	**allocate_args(char *cmd_str)
{
	char	**args;
	int		len;
	
	len = count_cmd_args(cmd_str);
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	return (args);
}

static int	count_arg_lenght(char *cmd_str, int i, bool *quotes)
{
	int	len;
	
	len = 0;
	while (cmd_str[i] && char_is_whitespace(cmd_str[i]))
		i++;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
		{
			len += quotes_offset(cmd_str + i, cmd_str[i]) - 2;
			*quotes = true;
			return (len);
		}
		while (cmd_str[i] && cmd_str[i] != '"' && cmd_str[i] != '\'' && !char_is_whitespace(cmd_str[i]))
		{
			len++;
			i++;
		}
	}
	return (len);
}

static char	*extract_arg(char *cmd_str, int *i)
{
	char	*arg;
	int		len;
	bool	quotes;

	quotes = false;
	len = count_arg_lenght(cmd_str, *i, &quotes);
	if (len <= 0)
		return (NULL);
	if (quotes)
		arg = create_quoted_arg(cmd_str, i, len);
	else
		arg = ft_substr(cmd_str, *i, len);
//	printf("cmd[%d] after ft_substr: %s\n", *i, arg);
	if (!arg)
		return (NULL);
	if (!quotes)
		*i = *i + len;
//	printf("index after creating arg: %d\n", *i);
	return (arg);
}

char	**split_cmd_args(char *cmd_str)
{
	char	**args;
	int		i;
	int		j;
	
	args = allocate_args(cmd_str);
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd_str[i])
	{
		while (cmd_str[i] && char_is_whitespace(cmd_str[i]))
			i++;
		if (!cmd_str[i])
			break ;
		args[j] = extract_arg(cmd_str, &i);
		if (!args[j])
		{
			free_2d_array(args);
			return (NULL);
		}
		j++;
	}
	args[j] = NULL;
	return (args);
}
