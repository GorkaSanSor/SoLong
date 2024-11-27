/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:22:39 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:06:54 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Chooses the corresponding player image based on the key pressed. */

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

/* Prints the player after it has moved, using the corresponding XPM image. */

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

/* Updates the player's position in the game structure. */

void	ft_copy_player_pos(t_data *game, t_pos *map_data)
{
	game->p_x_copy = map_data->p_x;
	game->p_y_copy = map_data->p_y;
}

/* Scans the map to check if there are still collectibles left */

int	ft_find_c(char **map)
{
	int	x;
	int	y;

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
