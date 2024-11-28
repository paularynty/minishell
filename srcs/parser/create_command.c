/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:31:03 by sniemela          #+#    #+#             */
/*   Updated: 2024/11/28 13:30:16 by sniemela         ###   ########.fr       */
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

static char	**split_cmd_args(char *cmd_str)
{
	char	**args;
	int		len;
	
	len = count_cmd_args(cmd_str);
	args = (char **)malloc(sizeof(char *) *(len + 1));
	if (!args)
		return (NULL);
	// not finished
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
