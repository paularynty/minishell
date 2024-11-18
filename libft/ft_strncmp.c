/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:49:38 by prynty            #+#    #+#             */
/*   Updated: 2024/04/26 10:21:34 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (s1[i] != '\0' && i < n)
	{
		if (p1[i] == p2[i])
			i++;
		else if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
	}
	if (i < n && p1[i] != '\0')
		return (p1[i] - p2[i]);
	if (i < n && p2[i] != '\0')
		return (p1[i] - p2[i]);
	return (0);
}
