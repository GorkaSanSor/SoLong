# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 12:25:37 by gsantill          #+#    #+#              #
#    Updated: 2024/11/05 15:13:06 by gsantill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables principales
NAME = so_long
CC = gcc #-g3 -fsanitize=address
CFLAGS = -Wall -Werror -Wextra -I$(LIBMLX)/include
RM = rm -rf
AR = ar rcs

# Colores
GREEN_PRE = '\033[32m'
RED_PRE = '\033[31m'
RESET_BLACK = '\033[0m'

# Librerías y paths externos
PRINTF_PATH = ./my_lib/ft_printf
PRINTF_A = $(PRINTF_PATH)/libftprintf.a

LIBFT_PATH = ./my_lib/libft
LIBFT_A = $(LIBFT_PATH)/libft.a

GNL_PATH = ./my_lib/get_next_line
GNL_A = $(GNL_PATH)/gnl.a

LIBMLX = ./MLX42
MLX_A = -L$(LIBMLX)/build -lmlx42 -lglfw -pthread -lm -lX11 -lXrandr -lXi -lXxf86vm -lXinerama -lXcursor

# Fuentes y objetos del proyecto
SRCS_PATH = ./srcs
SRCS = error_exit.c error_utils.c main.c map_error.c map.c move_utils.c movement.c textures.c
HEADER = $(SRCS_PATH)/so_long.h

OBJS_PATH = ./objs
OBJS = $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))

# Compilación de los objetos
$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c | $(OBJS_PATH)
	$(CC) $(CFLAGS) -c $^ -o $@

# Objetivo principal
all: libmlx $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	@echo $(GREEN_PRE)"LIBFT compiled!"$(RESET_BLACK)
	make -C $(PRINTF_PATH)
	@echo $(GREEN_PRE)"PRINTF compiled!"$(RESET_BLACK)
	make -C $(GNL_PATH)
	@echo $(GREEN_PRE)"GNL compiled!"$(RESET_BLACK)
	$(CC) $^ $(LIBFT_A) $(PRINTF_A) $(GNL_A) $(MLX_A) -o $@
	@echo $(GREEN_PRE)"so_long compiled!"$(RESET_BLACK)
	@echo "./so_long <.ber file> to run"

# Crear el directorio de objetos si no existe
$(OBJS_PATH):
	mkdir -p $@

# Compilar MLX42 con CMake
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo $(GREEN_PRE)"MLX compiled!"$(RESET_BLACK)

# Limpiar los archivos objeto
clean:
	@$(RM) $(OBJS_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(PRINTF_PATH) clean
	make -C $(GNL_PATH) clean
	@echo $(RED_PRE)"Object files deleted!"$(RESET_BLACK)

# Limpiar los archivos objeto y el ejecutable
fclean: clean
	@$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean
	make -C $(PRINTF_PATH) fclean
	make -C $(GNL_PATH) fclean
	@echo $(RED_PRE)"Executable deleted!"$(RESET_BLACK)

# Recompilar todo
re: fclean all

# Comprobación de Norminette
normi:
	norminette $(SRCS_PATH)/*.c $(HEADER)

.PHONY: all clean fclean re normi


