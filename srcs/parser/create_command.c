/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:31:03 by sniemela          #+#    #+#             */
/*   Updated: 2024/11/28 16:24:40 by sniemela         ###   ########.fr       */
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

	i = 0;
	args = 0;
	while (cmd_str[i])
	{
		while (cmd_str[i] && is_whitespace(cmd[i]))
			i++;
		if (!cmd_str[i])
			break ;
		args++;
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
			i += quotes_offset(cmd_str, cmd_str[i]);
		while (cmd_str[i] && cmd[i] != '"' && cmd[i] != '\''
			&& !is_whitespace(cmd[i]))
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

int		count_arg_lenght(char *cmd_str, int i)
{
	int	len;
	
	len = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
		{
			len += quotes_offset(cmd_str, cmd_str[i])
			break ;
		}
		while (cmd_str[i] != '"' && cmd_str[i] != '\'' && !is_whitespace(cmd[i]))
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*extract_arg(char *cmd_str, int *i)
{
	char	*arg;
	int		j;
	int		len;

	len = count_arg_length(cmd_str, *(i));
	arg = (char *)malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (NULL);
	j = *i;
	while (cmd_str[i])
	{
		if (cmd_str[i] == '"' || cmd_str[i] == '\'')
		{
			j += quotes_offset(cmd_str, cmd_str[i]);
			if (!ft_strlcat(arg, cmd_str + i, len))
			{
				free (arg);
				return (NULL);

				KESKEN!
		
	}
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
	if (!args || !tokenize_args(command, args))
	{
		ft_free_array(&args); // check later if in ft_free_array there's a check to avoid double free
		free(command);
		return (NULL);
	}
	ft_free_array(&args); // ft_free_array is made for 3D array
	return (command);
}
