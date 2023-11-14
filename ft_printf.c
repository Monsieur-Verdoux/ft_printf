/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:24:34 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/14 13:35:50 by akovalev         ###   ########.fr       */
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

void	ft_hex(unsigned int num, int *count, char c)
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
				ft_putchar_pf(((num / pow) - 10) + 'a', count);
			else
				ft_putchar_pf(((num / pow) - 10) + 'A', count);
		}
		else
			ft_putchar_pf((num / pow) + '0', count);
		num = num % pow;
		pow = pow / 16;
	}
}

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

static void	ft_phex(unsigned long int num, int *count)
{
	int					len;
	unsigned long int	pow;

	len = ft_plen_pf(num);
	pow = ft_ppow_pf(len - 1);
	while (pow > 0)
	{
		if (num / pow > 9)
		{
			ft_putchar_pf(((num / pow) - 10) + 'a', count);
		}
		else
			ft_putchar_pf((num / pow) + '0', count);
		num = num % pow;
		pow = pow / 16;
	}
}

void ft_pointer_pf(unsigned long int p, int *count)
{
	if (p == 0)
	{
		ft_putstr_pf("0x0", count);
		return ;
	}
	ft_putstr_pf("0x", count);
	ft_phex(p, count);
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
	else if (*str == 'p')
		ft_pointer_pf(((unsigned long int)va_arg(args, void *)), count);
	else if (*str == 'x' || *str == 'X')
		ft_hex(va_arg(args, unsigned int), count, *str);
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

	//ours = ft_printf("Testing for '123' %u\n", 123);
	//printf("count is %d\n", ours);
	//n = printf("Testing for '123' %u\n", 123);
	//printf("actual count is: %d\n", n);

	//ours = ft_printf("Testing for '' %p\n %p\n", LONG_MIN, LONG_MAX);
	//printf("ft_printf count is %d\n", ours);
	n = printf("Testing for '' %p\n %p\n", LONG_MIN, LONG_MAX);
	printf("printf count is: %d\n", n);
}*/
