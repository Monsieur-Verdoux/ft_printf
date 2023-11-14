/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:45:53 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/14 17:01:03 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_pf(char *str, int *count)
{
	if (str == NULL)
	{
		if (ft_putstr_pf("(null)", count) == -1)
			return (*count = -1);
		return (*count);
	}
	while (*str)
	{
		if (ft_putchar_pf(*str, count) == -1)
		{
			*count = -1;
			return (*count);
		}
		str++;
	}
	return (0);
}
