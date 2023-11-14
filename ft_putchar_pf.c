/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:45:01 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/14 17:00:55 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_pf(char c, int *count)
{
	int	buffer;

	buffer = write(1, &c, 1);
	if (buffer == -1)
	{
		*count = -1;
		return (*count);
	}
	(*count)++;
	return (0);
}
