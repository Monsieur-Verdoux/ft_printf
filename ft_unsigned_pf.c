/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_pf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:47:47 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/16 18:56:40 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_pf(unsigned int n, int *count)
{
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
