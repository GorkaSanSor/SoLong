# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 10:23:21 by gsantill          #+#    #+#              #
#    Updated: 2024/11/27 15:57:39 by gsantill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Imlx_linux -Isrc -O3
RM = rm -rf

# Colors
GREEN_PRE = '\033[32m'
RED_PRE = '\033[31m'
CYAN_PRE = '\033[36m'
MAGENTA_PRE = '\033[35m'
YELLOW_PRE = '\033[33m'
RESET_BLACK = '\033[0m'

# Paths
SRCS_DIR = src
OBJS_DIR = obj
LIBS_DIR = my_lib
MLX_DIR = mlx_linux
MLX_BUILD = $(MLX_DIR)/build

# Sources and Objects
SRCS = main.c error_exit.c error_utils.c map_error.c map.c \
	move_utils.c movement.c textures.c
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Libraries
PRINTF_PATH = $(LIBS_DIR)/ft_printf
GNL_PATH = $(LIBS_DIR)/ft_gnl

PRINTF_A = $(PRINTF_PATH)/libftprintf.a
GNL_A = $(GNL_PATH)/gnl.a

MLX_A = -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# ASCII Art
define SO_LONG
$(YELLOW_PRE)
        _______          _____                              
     ___|\     \    ____|\    \                             
    |    |\     \  /     /\    \                            
    |    |/____/| /     /  \    \                           
 ___|    \|   | ||     |    |    |                          
|    \    \___|/ |     |    |    |                          
|    |\     \    |\     \  /    /|                          
|\ ___\|_____|   | \_____\/____/ |                          
| |    |     |    \ |    ||    | /                          
 \|____|_____|     \|____||____|/                           
    \(    )/          \(    )/                              
     '    '            '    '                               
$(CYAN_PRE) 
 ____                _____  _____   ______         _____    
|    |          ____|\    \|\    \ |\     \    ___|\    \   
|    |         /     /\    \\\    \| \     \  /    /\    \  
|    |        /     /  \    \\|    \  \     ||    |  |____| 
|    |  ____ |     |    |    ||     \  |    ||    |    ____ 
|    | |    ||     |    |    ||      \ |    ||    |   |    |
|    | |    ||\     \  /    /||    |\ \|    ||    |   |_,  |
|____|/____/|| \_____\/____/ ||____||\_____/||\ ___\___/  /|
|    |     || \ |    ||    | /|    |/ \|   ||| |   /____ / |
|____|_____|/  \|____||____|/ |____|   |___|/ \|___|    | / 
  \(    )/        \(    )/      \(       )/     \( |____|/  
   '    '          '    '        '       '       '   )/     
                                                     '
$(RESET_BLACK)
endef
export SO_LONG

# Targets
all: $(PRINTF_A) $(GNL_A) $(NAME)

# Compile Libraries
$(PRINTF_A):
	@$(MAKE) -s -C $(PRINTF_PATH)
	@echo $(GREEN_PRE)"FT_PRINTF compiled!"$(RESET_BLACK)

$(GNL_A):
	@$(MAKE) -s -C $(GNL_PATH)
	@echo $(GREEN_PRE)"GET_NEXT_LINE compiled!"$(RESET_BLACK)

# Compile Project
$(NAME): $(OBJS)
	@echo "Compiling so_long"
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF_A) $(GNL_A) $(MLX_A) -o $(NAME)
	@echo $(GREEN_PRE)"SO_LONG compiled successfully!"$(RESET_BLACK)
	@echo "$$SO_LONG"

# Object Files Rule
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $< -> $@"

# MLX Compilation
libmlx:
	@echo "Compiling MLX"
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) > /dev/null
	@cmake --build $(MLX_BUILD) -j4 > /dev/null
	@echo $(GREEN_PRE)"MLX compiled!"$(RESET_BLACK)

# Clean Rules
clean:
	@$(RM) $(OBJS_DIR)
	@$(MAKE) -s -C $(PRINTF_PATH) clean
	@$(MAKE) -s -C $(GNL_PATH) clean
	@echo $(RED_PRE)"Object files cleaned!"$(RESET_BLACK)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(PRINTF_PATH) fclean
	@$(MAKE) -s -C $(GNL_PATH) fclean
	@echo $(RED_PRE)"All binaries cleaned!"$(RESET_BLACK)

re: fclean all

# Norminette Check
normi:
	@norminette $(SRCS_DIR)/*.c $(SRCS_DIR)/*.h

.PHONY: all clean fclean re normi