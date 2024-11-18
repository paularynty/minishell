/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:48:22 by prynty            #+#    #+#             */
/*   Updated: 2024/04/26 10:20:24 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t len)
{
	size_t				i;
	unsigned char		*dst;
	const unsigned char	*src;

	i = len;
	dst = (unsigned char *)s1;
	src = (const unsigned char *)s2;
	if (!dst && !src)
		return (NULL);
	if ((dst > src) && (dst < src + len) && (src < dst + len))
	{
		while (i--)
			dst[i] = src[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			*dst++ = *src++;
			i++;
		}
	}
	return (s1);
}
