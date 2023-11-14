# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akovalev <akovalev@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 11:32:21 by akovalev          #+#    #+#              #
#    Updated: 2023/11/13 11:41:55 by akovalev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

LIBFTD = libft

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(LIBFTD) bonus
	cp $(LIBFTD)/libft.a $(NAME)
	ar -crs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	make -C $(LIBFTD) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFTD) fclean

re: fclean all

.PHONY: all clean fclean re