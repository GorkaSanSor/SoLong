/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:22:39 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 10:28:55 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
This function chooses the corresponding image of the player depending on the
key that has been pressed. xpm_path is initialized to NULL to avoid an error
on the compiler saying that xpm_path "might not be initialized" in all the
cases
*/

char	*ft_player_look(char direction)
{
	char	*xpm_path;
	
	xpm_path = NULL;
	if (direction == 'U')
		xpm_path = PLAYER_U;
	else if (direction == 'D')
		xpm_path = PLAYER_D;
	else if (direction == 'L')
		xpm_path = PLAYER_L;
	else if (direction == 'R')
		xpm_path = PLAYER_R;
	return (xpm_path);
}

/*
This function prints the player after it has moved. Depending on the direction
it prints the corresponding XPM image. Notice that x and y received are
memory addresses
*/

int	ft_print_player(t_data *game, int *x, int *y, char direction)
{
	void	*img;
	int		img_height;
	int		img_width;
	
	img = mlx_xpm_file_to_image(game->mlx, ft_player_look(direction), \
	&img_width, &img_height);
	if (!img)
		ft_error_exit(INVALID_XPM, game);
	if (direction == 'U')
		mlx_put_image_to_window(game->mlx, game->window, \
		img, *x * 80, (--(*y) * 80));
	if (direction == 'D')
		mlx_put_image_to_window(game->mlx, game->window, \
		img, *x * 80, (++(*y) * 80));
	if (direction == 'L')
		mlx_put_image_to_window(game->mlx, game->window, \
		img, (--(*x)) * 80, (*y * 80));
	if (direction == 'R')
		mlx_put_image_to_window(game->mlx, game->window, \
		img, (++(*x)) * 80, (*y * 80));
	mlx_destroy_image(game->mlx, img);
	return (0);
}

/*
This function gets the position of the player in the map. It then updats the
coordinates in the map_data struct and copies them to the game struct
*/

void	ft_copy_player_pos(t_data *game, t_pos *map_data)
{
	game->p_x_copy = map_data->p_x;
	game->p_y_copy = map_data->p_y;
}

/*
Scans the map to check if there are still collectibles left
*/

int	ft_find_c(char **map)
{
	int	x;
	int y;
	
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'C')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}