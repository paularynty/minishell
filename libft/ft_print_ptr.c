/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:56:04 by prynty            #+#    #+#             */
/*   Updated: 2024/07/21 15:44:55 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char *hex_digit)
{
	if (write(1, &hex_digit[0], 1) < 0)
		return (-1);
	return (3);
}

int	ft_print_ptr(unsigned long long ptr)
{
	char	*hex_digit;
	char	buffer[16];
	int		len;
	int		index;

	len = 0;
	index = 0;
	hex_digit = LOW_HEX_BASE;
	if (write(1, "0x", 2) < 0)
		return (-1);
	len = len + 2;
	if (ptr == 0)
		return (check(hex_digit));
	while (ptr > 0)
	{
		buffer[index++] = hex_digit[ptr % 16];
		ptr = ptr / 16;
	}
	while (index > 0)
	{
		if (write(1, &buffer[--index], 1) < 0)
			return (-1);
		len++;
	}
	return (len);
}
