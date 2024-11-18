/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:21:40 by prynty            #+#    #+#             */
/*   Updated: 2024/07/21 15:44:09 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (*str++)
		i++;
	return (i);
}

char	*gnl_strchr(char *str, char chr)
{
	while (*str)
	{
		if (*str == chr)
			return (str);
		str++;
	}
	return (NULL);
}

void	gnl_bzero(char *buf, size_t size)
{
	while (size-- > 0)
		buf[size] = '\0';
}

void	gnl_copy(char *dst, char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*gnl_strjoin(char *s2, char *s1, size_t len)
{
	char			*s3;
	char			*ptr;
	size_t			total_len;
	unsigned int	i;

	if (!*s1)
		return (s2);
	if (s2 == NULL || s1 == NULL)
		return (NULL);
	total_len = gnl_strlen(s2) + len + 1;
	s3 = malloc(total_len);
	if (s3 == NULL)
	{
		free(s2);
		return (NULL);
	}
	i = 0;
	ptr = s2;
	while (*s2)
		s3[i++] = *s2++;
	while (i < total_len - 1)
		s3[i++] = *s1++;
	free(ptr);
	s3[i] = '\0';
	return (s3);
}
