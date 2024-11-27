/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:26 by prynty            #+#    #+#             */
/*   Updated: 2024/11/27 11:29:43 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/********************************
 * 
 * The insides of the quotes are their own argument, so we count how long this
 * argument is (including quotes)
 * 
 ******************************/

int	quotes_offset(const char *input, char quote)
{
	int	offset;

	offset = 1; // we already have quotes opened, so we start with 1 instead of 1
	while (input[offset] && input[offset] != quote)
		offset++;
	// if (input[offset] == '\0')
	//	OPEN_QUOTES = 1; we could have a flag for open quotes later, it's optional
	return (offset); // check logic for open quotes later
}

/********************************
 * 
 * we count how many pipes occur
 * 
 ******************************/

int	count_pipes(const char *input)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input, input[i]); // we move index until quotes are closed
		else if (input[i] == '|')
			pipes++;
		i++;
	}
	// if (input[i -1] == '|')
	// 	OPEN_PIPES = 1, we could have a flag for open pipe later, it's optional
	return (pipes);
}

/********************************
 * 
 * custom strndup which could be added to libft
 *  The strndup() function is similar to strdup, but copies at most n bytes.  If s is
 *  longer than n, only n bytes are copied, and  a  terminating  null  byte	
 *  ('\0') is added.
 *
 * 
 ******************************/

char	*ft_strndup(const char *src, size_t n)
{
	char	*dup;
	size_t	i;

	i = 0;
	dup = (char *)malloc(sizeof(*src) * (n + 1));
	if (!dup)
		return (NULL);
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	process_input(const char *input, char **cmd, int *j, int *start)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i += quotes_offset(input + i, input[i]);
		else if (input[i] == '|')
		{
			cmd[*j] = ft_strndup(input + *start, i - *start);
			if (!cmd[*j])
				return (0); // we free in the calling function
			(*j)++;
			*start = i + 1;
		}
		i++;
	}
	return (i);
}

char	**allocate_cmd_array(const char *input)
{
	int	cmd_count;
	int	pipes;
	char	**cmd;

	pipes = count_pipes(input);
	cmd_count = pipes + 1;
	cmd = (char **)malloc(sizeof(char *)*(cmd_count + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	**split_by_pipes(const char *input)
{
	char **cmd;
	int	j;
	int	start;
	int	end;

	cmd = allocate_cmd_array(input);
	if (!cmd)
		return (NULL);
	j = 0;
	start = 0;
	end = process_input(input, cmd, &j, &start);
	if (!end || (start < end && !(cmd[j++] = ft_strndup(input + start, end - start))))
	{
		while (j > 0)
			free(cmd[--j]);
		free(cmd);
		return (NULL);
	}
	cmd[j] = NULL;
	return (cmd);
}

void	tokenizer(const char *input)
{
	char	**cmd;

	cmd = split_by_pipes(input);
	// if (!cmd)
	// 	// we have to free input, but nothing else should be allocated?

}

