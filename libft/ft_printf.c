/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prynty <prynty@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:32:09 by prynty            #+#    #+#             */
/*   Updated: 2024/07/21 15:45:01 by prynty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_flags(va_list args, const char format)
{
	unsigned int	len;

	len = 0;
	if (format == 'c')
		len += (ft_print_char(va_arg(args, int)));
	else if (format == 's')
		len += (ft_print_str(va_arg(args, char *)));
	else if (format == 'p')
		len += (ft_print_ptr((unsigned long long)(va_arg(args, void *))));
	else if (format == 'd' || format == 'i')
		len += (ft_print_nbr(va_arg(args, int)));
	else if (format == 'u')
		len += (ft_print_nbr_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		len += (ft_print_hex(va_arg(args, unsigned int), 'x'));
	else if (format == 'X')
		len += (ft_print_hex(va_arg(args, unsigned int), 'X'));
	else if (format == '%')
	{
		len += 1;
		if (ft_print_char('%') < 0)
			return (-1);
	}
	return (len);
}

static int	parse_format(va_list args, const char *str, unsigned int len)
{
	int	temp;

	len = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			if (*str == '\0')
				break ;
			if (ft_strchr("cspdiuxX%", *str))
				temp = format_flags(args, *str);
			else
				return (-1);
		}
		else
			temp = ft_print_char(*str);
		if (temp < 0)
			return (-1);
		len += temp;
		str++;
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	len;	

	len = 0;
	va_start(args, str);
	len = parse_format(args, str, len);
	va_end(args);
	return (len);
}
