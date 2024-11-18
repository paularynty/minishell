/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:28:30 by prynty            #+#    #+#             */
/*   Updated: 2024/04/26 11:08:02 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t		destlen;
	size_t		total_len;

	destlen = 0;
	if ((!dest || !src) && !destsize)
		return (0);
	while (dest[destlen] && destlen < destsize)
		destlen++;
	if (destlen < destsize)
		total_len = destlen + ft_strlen(src);
	else
		return (destsize + ft_strlen(src));
	while (*src && (destlen + 1) < destsize)
	{
		dest[destlen] = *src++;
		destlen++;
	}
	dest[destlen] = '\0';
	return (total_len);
}
