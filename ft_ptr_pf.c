/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:51:20 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/16 18:57:03 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long int	ft_ppow_pf(int pow)
{
	if (pow == 0)
		return (1);
	return (ft_ppow_pf(pow - 1) * 16);
}

static int	ft_plen_pf(unsigned long int num)
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

static int	ft_phex(unsigned long int num, int *count)
{
	int					len;
	unsigned long int	pow;

	len = ft_plen_pf(num);
	pow = ft_ppow_pf(len - 1);
	while (pow > 0)
	{
		if (num / pow > 9)
		{
			if (ft_putchar_pf(((num / pow) - 10) + 'a', count) == -1)
				return (-1);
		}
		else
		{
			if (ft_putchar_pf((num / pow) + '0', count) == -1)
				return (-1);
		}
		num = num % pow;
		pow = pow / 16;
	}
	return (0);
}

int	ft_ptr_pf(unsigned long int p, int *count)
{
	if (p == 0)
	{
		if (ft_putstr_pf("0x0", count) == -1)
			return (-1);
	}
	else
	{
		if (ft_putstr_pf("0x", count) == -1)
			return (-1);
		ft_phex(p, count);
	}
	return (0);
}
