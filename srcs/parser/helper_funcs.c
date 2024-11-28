/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:42:29 by sniemela          #+#    #+#             */
/*   Updated: 2024/11/28 12:55:49 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parser.h"

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