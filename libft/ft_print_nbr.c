/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:58 by prynty            #+#    #+#             */
/*   Updated: 2024/07/21 15:44:53 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_nbr(int n)
{
	char	c;

	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) < 0)
			return (-1);
		return (11);
	}
	if (n < 0)
	{
		if (write(1, "-", 1) < 0)
			return (-1);
		n = -n;
	}
	if (n >= 10)
	{
		if (write_nbr(n / 10) < 0)
			return (-1);
	}
	c = (n % 10) + '0';
	if (ft_print_char(c) < 0)
		return (-1);
	return (1);
}

int	ft_print_nbr(int n)
{
	unsigned int	len;
	int				nbr;
	int				value;

	nbr = n;
	len = 1;
	if (n < 0)
	{
		nbr = -n;
		len++;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		len++;
	}
	value = write_nbr(n);
	if (value == -1 || value == 11)
		return (value);
	return (len);
}
