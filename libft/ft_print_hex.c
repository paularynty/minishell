/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:15 by prynty            #+#    #+#             */
/*   Updated: 2024/07/21 15:44:48 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned long long n, const char format)
{
	char	*hex_digit;
	char	digit;
	int		len;
	int		retval;

	len = 0;
	if (format == 'x')
		hex_digit = LOW_HEX_BASE;
	else
		hex_digit = UP_HEX_BASE;
	if (n >= 16)
	{
		retval = ft_print_hex(n / 16, format);
		if (retval == -1)
			return (retval);
		len = len + retval;
	}
	digit = hex_digit[n % 16];
	if (ft_print_char(digit) < 0)
		return (-1);
	len++;
	return (len);
}
