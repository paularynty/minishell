/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:12:39 by prynty            #+#    #+#             */
/*   Updated: 2024/07/21 15:44:58 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(const char *str)
{
	int	i;
	int	temp;

	i = 0;
	temp = i;
	if (!str)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (str[i])
	{
		i += ft_print_char(str[i]);
		if (i < temp)
			return (-1);
	}
	return (i);
}
