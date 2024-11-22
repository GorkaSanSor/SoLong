# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 15:43:03 by gsantill          #+#    #+#              #
#    Updated: 2024/10/24 15:29:38 by gsantill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = 		./ft_printf.c			\
			./ft_print_nbr.c		\
			./ft_print_char.c		\
			./ft_print_str.c		\
			./ft_print_pointer.c	\
			./ft_print_hex.c

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a
HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
