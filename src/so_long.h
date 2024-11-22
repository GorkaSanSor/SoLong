/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:15:32 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/22 10:42:20 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 64

#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../mlx_linux/mlx.h"
#include "../my_lib/ft_printf/ft_printf.h"
#include "../my_lib/get_next_line/gnl.h"
//#include "../my_lib/libft/libft.h"

/*---------------------------------ERROR TYPES--------------------------------*/

# define WRONG_ARGS 100
# define EMPTY_MAP 101
# define INVALID_MAP 102
# define INVALID_WALLS 103
# define INVALID_OBJECTS 104
# define INVALID_PATH 105
# define INVALID_XPM 106
# define MANUAL_CLOSE 107
# define WRONG_EXT 108
# define INVALID_FLOOR 109

/*--------------------------------XPM CONSTANTS-------------------------------*/

// Paths to assets
# define WALL "./assets/Wall.xpm"
# define FLOOR "./assets/Floor.xpm"
# define COLLECT "./assets/Collectible.xpm"
# define EXIT "./assets/Exit.xpm"
# define PLAYER_U "./assets/PlayerU.xpm"
# define PLAYER_D "./assets/PlayerD.xpm"
# define PLAYER_L "./assets/PlayerL.xpm"
# define PLAYER_R "./assets/PlayerR.xpm"

typedef struct s_textures
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*exit;
	void	*player_u;
	void	*player_d;
	void	*player_l;
	void	*player_r;
}	t_textures;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	char		**map;
	int			map_rows;
	int			p_x_copy;
	int			p_y_copy;
	int			final_move;
	t_textures	textures; // Añadimos las texturas aquí
}	t_data;


typedef struct s_pos
{
	int	p_x;
	int	p_y;
	int	size_x;
	int	size_y;
}	t_pos;

/*--------------------------------error_exit.c--------------------------------*/
int		ft_check_extension(t_data *game, char *str);
void	ft_free_map(char **map);
int		ft_exit_ok(t_data *game);
void	ft_error_exit(int err_type, t_data *game);

/*--------------------------------error_utils.c-------------------------------*/
char	ft_get_object(char **map, char c);
int		ft_check_fill(char **map_cpy);
void	ft_fill(char **map_copy, t_pos map_data, int x, int y);
void	ft_find_player(char **map, t_pos *map_data);
char	**ft_copy_map(char **map);

/*----------------------------------map_error.c-------------------------------*/
int		ft_map_is_error(t_data *game);

/*------------------------------------map.c-----------------------------------*/
int		ft_line_lenght(char *str);
void	ft_save_map(t_data *game, char *str);
char	**ft_map_fill(int *rows, char *str);
int		ft_map_floor(char **map);

/*---------------------------------move_utils.c-------------------------------*/
void	ft_copy_player_pos(t_data *game, t_pos *map_data);

/*----------------------------------movement.c--------------------------------*/
int		ft_input(int key, t_data *game);

/*----------------------------------textures.c--------------------------------*/
void	ft_scan_map(t_data *game);


#endif