/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:49:29 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/16 18:57:32 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_pow_pf(int pow)
{
	if (pow == 0)
		return (1);
	return (ft_pow_pf(pow - 1) * 16);
}

static int	ft_len_pf(unsigned int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	ft_hex_pf(unsigned int num, int *count, char c)
{
	int				len;
	unsigned int	pow;

	len = ft_len_pf(num);
	pow = ft_pow_pf(len - 1);
	while (pow >= 1)
	{
		if (num / pow > 9)
		{
			if (c == 'x')
			{
				if (ft_putchar_pf(((num / pow) - 10) + 'a', count) == -1)
					return (-1);
			}
			else
				if (ft_putchar_pf(((num / pow) - 10) + 'A', count) == -1)
					return (-1);
		}
		else
			if (ft_putchar_pf((num / pow) + '0', count) == -1)
				return (-1);
		num = num % pow;
		pow = pow / 16;
	}
	return (0);
}
