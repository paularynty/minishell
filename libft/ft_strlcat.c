/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:28:30 by prynty            #+#    #+#             */
/*   Updated: 2024/11/27 11:48:32 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t		len;
	size_t		total_len;

	len = 0;
	if ((!dest || !src) && !destsize)
		return (0);
	while (dest[len] && len < destsize)
		len++;
	if (len < destsize)
		total_len = len + ft_strlen(src);
	else
		return (destsize + ft_strlen(src));
	while (*src && (len + 1) < destsize)
	{
		dest[len] = *src++;
		len++;
	}
	dest[len] = '\0';
	return (total_len);
}
