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
			i += quote_offset(cmd_str + i, cmd_str[i]);
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

static int	count_arg_length(char *cmd_str, int i, bool *quotes)
{
	int	len;
	
	len = 0;
	while (cmd_str[i] && char_is_whitespace(cmd_str[i]))
		i++;
	while (cmd_str[i] && !char_is_whitespace(cmd_str[i]))
	{
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
		{
			len += quote_offset(cmd_str + i, cmd_str[i]) - 2;
			*quotes = true;
			i += quote_offset(cmd_str + i, cmd_str[i]);
			// printf("len after quote_offset: %d\n", len);
			// printf("i after quote_offset: %d\n", i);
			// printf("cmd_str pointer after quote_offset: %s\n", cmd_str + i);
		}
		else
		{
			len++;
			i++;
		}
		// check_print("len: %d\n", len);
		// check_print("i: %d\n", i);
		// check_print("cmd_str pointer: %s\n", cmd_str + i);
	}
	// check_print("len: %d\n", len);
	// check_print("i: %d\n", i);
	return (len);
}

static char	*extract_arg(char *cmd_str, int *i)
{
	char	*arg;
	int		len;
	bool	quotes;

	quotes = false;
	len = count_arg_length(cmd_str, *i, &quotes);
	// printf("arg len: %d\n", len);
	if (quotes)
	{	
		// printf("we're creating a quoted arg\n");
		arg = create_quoted_arg(cmd_str, i, len);
	}
	else
		arg = ft_substr(cmd_str, *i, len);
	// check_print("cmd[%d] after ft_substr: %s\n", *i, arg);
	if (!arg)
		return (NULL);
	if (!quotes)
		*i = *i + len;
	// check_print("index after creating arg: %d\n", *i);
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
		// check_print("before extract_arg\n");
		args[j] = extract_arg(cmd_str, &i);
		// printf("Argument %d: |%s|\n", j, args[j]);
		if (!args[j])
		{
			ft_free_array(&args);
			return (NULL);
		}
		j++;
		i++;
	}
	args[j] = NULL;
	return (args);
}
