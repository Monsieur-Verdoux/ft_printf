/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:24:34 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/14 11:47:48 by akovalev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Program name libftprintf.a
Turn in files Makefile, *.h, * / *.h, *.c, * / *.c
Makefile NAME, all, clean, fclean, re
External functs. malloc, free, write,
va_start, va_arg, va_copy, va_end
Libft authorized Yes
Description Write a library that contains ft_printf(), a
function that will mimic the original printf()
Flags: cspdiuxX%*/

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>

int	ft_putchar_pf(char c, int *count)
{
	int	buffer;

	buffer = write(1, &c, 1);
	if (buffer == -1)
		return (-1);
	(*count)++;
	return (0);
}

int	ft_putstr_pf(char *str, int *count)
{
	if (str == NULL)
	{
		ft_putstr_pf("(null)", count);
		return (-1);
	}
	while (*str)
	{
		ft_putchar_pf(*str, count);
		str++;
	}
	return (0);
}

void	ft_putnbr_pf(int n, int *count)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count = *count + 11;
		return ;
	}
	if (n < 0)
	{
		ft_putchar_pf('-', count);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_pf(n / 10, count);
		n = n % 10;
	}
	if (n <= 9)
	{
		ft_putchar_pf(n + 48, count);
	}
}

void	ft_unsigned_pf(unsigned int n, int *count)
{
	if (n > 9)
	{
		ft_putnbr_pf(n / 10, count);
		n = n % 10;
	}
	if (n <= 9)
	{
		ft_putchar_pf(n + 48, count);
	}
}
/*{
	char			*array;
	size_t			len;
	unsigned int	nb;

	nb = n;
	len = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		len++;
	}
	array = ft_calloc((len + 1), sizeof(char));
	if (array == NULL)
		return ;
	while (len > 0)
	{
		array[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	ft_putstr_pf(array, count);
	free (array);
}*/

ft_hex_lower(unsigned int number, int *count)
{
	
}

void	determine_format(va_list args, char *str, int *count)
{
	if (*str == 'c')
		ft_putchar_pf(va_arg(args, int), count);
	else if (*str == 's')
		ft_putstr_pf(va_arg(args, char *), count);
	else if (*str == '%')
		ft_putchar_pf('%', count);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr_pf(va_arg(args, int), count);
	else if (*str == 'u')
		ft_unsigned_pf(va_arg(args, unsigned int), count);
	else if (*str == 'x')
		ft_hex_lower(va_arg(args, unsigned int), count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			determine_format(args, (char *)str, &count);
			str++;
		}
		else
		{
			ft_putchar_pf(*str, &count);
			str++;
		}
	}
	va_end (args);
	return (count);
}

/*int	main(void)
{
	int n;
	int ours;
	
	//ours = ft_printf("Testing for 'h': %c\n and for 'sup': %s\n and for '-2147483648': %d\n", 'h', "sup", -2147483648);
	//printf("count is %d\n", ours);
	//n = printf("Testing for 'h': %c\n and for 'sup': %s\n and for '-2147483648': %d\n", 'h', "sup", -2147483648);
	//printf("actual count is: %d\n", n);

	//ours = ft_printf("%s", (char *)NULL);
	//printf("count is %d\n", ours);
	//n = printf("%s", (char *)NULL);
	//printf("actual count is: %d\n", n);

	ours = ft_printf("Testing for '123' %u\n", 123);
	printf("count is %d\n", ours);
	n = printf("Testing for '123' %u\n", 123);
	printf("actual count is: %d\n", n);
}*/
