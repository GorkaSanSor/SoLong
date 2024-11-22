# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 15:23:42 by gsantill          #+#    #+#              #
#    Updated: 2024/11/22 11:59:11 by gsantill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror

FT_PRINTF_DIR = ft_printf
GNL_DIR = get_next_line

FT_PRINTF_SRCS = $(wildcard $(FT_PRINTF_DIR)/*.c)
GNL_SRCS = $(wildcard $(GNL_DIR)/*.c)

FT_PRINTF_OBJS = $(FT_PRINTF_SRCS:.c=.o)
GNL_OBJS = $(GNL_SRCS:.c=.o)

NAME = libftprintf.a

# Incluir los headers
INCLUDES = -I$(FT_PRINTF_DIR) -I$(GNL_DIR)

all: $(NAME)

$(NAME): $(FT_PRINTF_OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(FT_PRINTF_OBJS) $(GNL_OBJS)  # Generamos la librería sin libft

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(FT_PRINTF_OBJS) $(GNL_OBJS)  # Eliminamos los objetos de libft

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

