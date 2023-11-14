/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:24:34 by akovalev          #+#    #+#             */
/*   Updated: 2023/11/14 16:33:05 by akovalev         ###   ########.fr       */
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
	{
		*count = -1;
		return (*count);
	}
	(*count)++;
	return (0);
}

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

int	ft_putnbr_pf(int n, int *count)
{
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (*count = -1);
		*count = *count + 11;
		return (*count);
	}
	if (n < 0)
	{
		if (ft_putchar_pf('-', count) == -1)
			return (*count = -1);
		n = -n;
	}
	if (n > 9)
	{
		if (ft_putnbr_pf(n / 10, count) == -1)
			return (*count = -1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (ft_putchar_pf(n + 48, count) == -1)
			return (*count = -1);
	}
	return (*count);
}

int	ft_unsigned_pf(unsigned int n, int *count)
{
	if (n > 9)
	{
		if (ft_putnbr_pf(n / 10, count) == -1)
			return (*count = -1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (ft_putchar_pf(n + 48, count) == -1)
			return (*count = -1);
	}
	return (*count);
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

int	ft_hex(unsigned int num, int *count, char c)
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
					return (*count = -1);
			}
			else
				if (ft_putchar_pf(((num / pow) - 10) + 'A', count) == -1)
					return (*count = -1);
		}
		else
			if (ft_putchar_pf((num / pow) + '0', count))
				return (*count = -1);
		num = num % pow;
		pow = pow / 16;
	}
	return (*count);
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
				return (*count = -1);
		}
		else
		{
			if (ft_putchar_pf((num / pow) + '0', count) == -1)
				return (*count = -1);
		}
		num = num % pow;
		pow = pow / 16;
	}
	return (*count);
}

int	ft_ptr_pf(unsigned long int p, int *count)
{
	if (p == 0)
	{
		if (ft_putstr_pf("0x0", count) == -1)
		{
			*count = -1;
			return (*count);
		}
	}
	else
	{
		if (ft_putstr_pf("0x", count) == -1)
		{
			*count = -1;
			return (*count);
		}
		ft_phex(p, count);
	}
	return (*count);
}

static int	determine_format(va_list args, char *str, int *count)
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
		return (ft_hex(va_arg(args, unsigned int), count, *str));
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
			if (determine_format(args, (char *)str, &count) == -1)
				return (count = -1);
			str++;
		}
		else
		{
			if (ft_putchar_pf(*str, &count))
				return (count = -1);
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
	//n = printf("Testing for '' %p\n %p\n", LONG_MIN, LONG_MAX);
	//printf("printf count is: %d\n", n);

	ours = ft_printf("\001\002\007\v\010\f\r\n");
	printf("ft_printf count is %d\n", ours);
	n = printf("\001\002\007\v\010\f\r\n");
	printf("printf count is: %d\n", n);
}*/
