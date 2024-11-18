/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:53 by prynty            #+#    #+#             */
/*   Updated: 2024/09/06 18:05:19 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	count_rows(char const *str, char c)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			rows++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (rows);
}

char	**ft_split(char const *str, char c)
{
	char	**array;
	char	*wordstart;
	int		i;

	array = (char **)malloc(sizeof(char *) * (count_rows(str, c) + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			wordstart = (char *)str;
			while (*str && *str != c)
				str++;
			array[i] = ft_substr(wordstart, 0, str - wordstart);
			if (!**array)
				return (free_array(array));
			i++;
		}
		else
			str++;
	}
	array[i] = NULL;
	return (array);
}
