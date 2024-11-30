/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:31:03 by sniemela          #+#    #+#             */
/*   Updated: 2024/11/30 15:26:25 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

static int	is_whitespace(char c)
{
	if (c != 32 && (c < 9 || c > 13))
		return (FALSE);
	return (TRUE);
}

static int	count_cmd_args(char *cmd_str)
{
	int	i;
	int	args;
//	int	offset; lets add check later to the code (offset == -1)  to check  whether quotes remained open
// 	offset = quotes_offset(cmd_str + i,  cmd_str[i]);
//  if (offset == -1) pyydetaan jossain vaiheessa userilta inputtia kunnes sulkuquote tulee
	i = 0;
	args = 0;
	while (cmd_str[i])
	{
		while (cmd_str[i] && is_whitespace(cmd_str[i]))
			i++;
		if (!cmd_str[i])
			break ;
		args++;
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
			i += quotes_offset(cmd_str + i, cmd_str[i]);
		while (cmd_str[i] && cmd_str[i] != '"' && cmd_str[i] != '\''
			&& !is_whitespace(cmd_str[i]))
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

static int	count_arg_lenght(char *cmd_str, int i)
{
	int	len;
	
	len = 0;
	while (cmd_str[i]  && is_whitespace(cmd_str[i]))
		i++;
	if (cmd_str[i] == '"' || cmd_str[i] == '\'')
	{
		len = quotes_offset(cmd_str + i, cmd_str[i]);
		return (len);
	}
	while (cmd_str[i] != '"' && cmd_str[i] != '\'' && !is_whitespace(cmd_str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*extract_arg(char *cmd_str, int *i)
{
	char	*arg;
	int		len;

	len = count_arg_lenght(cmd_str, *i);
	if (len <= 0)
		return (NULL);
	arg = ft_substr(cmd_str, *i, len);
	if (!arg)
		return (NULL);
	*i = *i + len;
	return (arg);
}

static char	**split_cmd_args(char *cmd_str)
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
		while (cmd_str[i] && is_whitespace(cmd_str[i]))
			i++;
		if (!cmd_str[i])
			break ;
		args[j] = extract_arg(cmd_str, &i);
		if (!args[j])
		{
			ft_free_array(&args);
			return (NULL);
		}
		j++;
	}
	args[j] = NULL;
	return (args);
}

static t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->tokens = NULL;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	cmd->next = NULL;
	return (cmd);
}

t_command	*create_command(char *cmd_str)
{
	t_command	*command;
	char		**args;

	command = init_command();
	if (!command)
		return (NULL);
	args = split_cmd_args(cmd_str);
	// DEBUGGAUSTA VARTEN:
	int k = 0;
	printf("split_cmd_args jalkeen: \n");
	while (args[k] != NULL)
	{
		printf("arg %d: |%s|\n", k+1, args[k]);
		k++;
	}
	printf("ennen tokenize_argsia\n");
//endif
	if (!args || !tokenize_args(command, args))
	{
		ft_free_array(&args); // check later if in ft_free_array there's a check to avoid double free
		free(command);
		return (NULL);
	}
	printf("tokenize_argsin jalkeen\n");
	printf("command->tokens: %p\n", command->tokens);
    t_token *temp = command->tokens;
    while (temp)
    {
        printf("Token: Type = %d, Value = |%s|\n", temp->type, temp->value);
        temp = temp->next;
    }
	ft_free_array(&args); // ft_free_array is made for 3D array
	command->next  = NULL;
	return (command);
}
