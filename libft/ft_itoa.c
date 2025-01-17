/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:32:13 by sniemela          #+#    #+#             */
/*   Updated: 2025/01/16 21:24:59 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_put_nbr(int nb, char *str, int *i)
{
	if (nb < 10)
	{
		str[*i] = nb + '0';
		(*i)++;
	}
	if (nb > 9)
	{
		ft_put_nbr(nb / 10, str, i);
		ft_put_nbr(nb % 10, str, i);
	}
	return (str);
}

static char	*allocate_memory(int len)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (str);
}

static int	count_len(int nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
		len = 2;
	while (nbr > 9 || nbr < -9)
	{
		len++;
		nbr = nbr / 10;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	len = count_len(nbr);
	str = allocate_memory(len);
	if (!str)
		return (NULL);
	if (nbr == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", len + 1);
		return (str);
	}
	if (nbr < 0)
	{
		str[i] = '-';
		nbr = nbr * (-1);
		i++;
	}
	ft_put_nbr(nbr, str, &i);
	str[i] = '\0';
	return (str);
}
