# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 11:32:21 by akovalev          #+#    #+#              #
#    Updated: 2023/11/14 18:25:24 by akovalev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
		ft_putchar_pf.c \
		ft_putstr_pf.c \
		ft_putnbr_pf.c \
		ft_unsigned_pf.c \
		ft_hex_pf.c \
		ft_ptr_pf.c \

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re