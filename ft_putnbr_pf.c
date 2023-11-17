/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:46:23 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/16 18:56:31 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pf(int n, int *count)
{
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		*count = *count + 11;
		return (0);
	}
	if (n < 0)
	{
		if (ft_putchar_pf('-', count) == -1)
			return (-1);
		n = -n;
	}
	if (n > 9)
	{
		if (ft_putnbr_pf(n / 10, count) == -1)
			return (-1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (ft_putchar_pf(n + 48, count) == -1)
			return (-1);
	}
	return (0);
}
