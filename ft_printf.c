/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:24:34 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/14 18:45:20 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_pf(va_list args, char *str, int *count)
{
	if (*str == 'c')
		return (ft_putchar_pf(va_arg(args, int), count));
	else if (*str == 's')
		return (ft_putstr_pf(va_arg(args, char *), count));
	else if (*str == '%')
		return (ft_putchar_pf('%', count));
	else if (*str == 'd' || *str == 'i')
		return (ft_putnbr_pf(va_arg(args, int), count));
	else if (*str == 'u')
		return (ft_unsigned_pf(va_arg(args, unsigned int), count));
	else if (*str == 'p')
		return (ft_ptr_pf(((unsigned long int)va_arg(args, void *)), count));
	else if (*str == 'x' || *str == 'X')
		return (ft_hex_pf(va_arg(args, unsigned int), count, *str));
	return (*count = -1);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	if (!str)
		return (-1);
	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (ft_format_pf(args, (char *)str, &count) == -1)
				return (count = -1);
			str++;
		}
		else
		{
			if (ft_putchar_pf(*str, &count) == -1)
				return (count = -1);
			str++;
		}
	}
	va_end (args);
	return (count);
}
