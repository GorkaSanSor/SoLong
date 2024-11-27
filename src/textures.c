/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:04:27 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 13:15:57 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Converts the XPM file to an image and displays it in the window */

static void	ft_put_image(t_data *game, char *c, int x, int y)
{
	void	*img;
	int		img_w;
	int		img_h;

	img = mlx_xpm_file_to_image(game->mlx, c, &img_w, &img_h);
	if (!img)
		ft_error_exit(INVALID_XPM, game);
	mlx_put_image_to_window(game->mlx, game->window, img, x, y);
	mlx_destroy_image(game->mlx, img);
}
/* Loads the corresponding image for a character on the map */

static void	ft_load_texture(t_data *game, char c, int x, int y)
{
	if (c == '1')
		ft_put_image(game, WALL, x, y);
	else if (c == '0')
		ft_put_image(game, FLOOR, x, y);
	else if (c == 'P')
		ft_put_image(game, PLAYER_D, x, y);
	else if (c == 'C')
		ft_put_image(game, COLLECT, x, y);
	else if (c == 'E')
		ft_put_image(game, EXIT, x, y);
	else if (c == 'O')
		ft_put_image(game, EXIT_O, x, y);
}

/* Frees all loaded textures */
void	ft_free_textures(t_data *game)
{
	if (game->textures.wall)
		mlx_destroy_image(game->mlx, game->textures.wall);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx, game->textures.floor);
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx, game->textures.collectible);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx, game->textures.exit);
	if (game->textures.exit_o)
		mlx_destroy_image(game->mlx, game->textures.exit_o);
	if (game->textures.player_u)
		mlx_destroy_image(game->mlx, game->textures.player_u);
	if (game->textures.player_d)
		mlx_destroy_image(game->mlx, game->textures.player_d);
	if (game->textures.player_l)
		mlx_destroy_image(game->mlx, game->textures.player_l);
	if (game->textures.player_r)
		mlx_destroy_image(game->mlx, game->textures.player_r);
}

/* Scans the map and loads textures for each character */
void	ft_scan_map(t_data *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	y = 0;
	while (game->map[i])
	{
		x = 0;
		j = 0;
		while (game->map[i][j] != '\0')
		{
			ft_load_texture(game, game->map[i][j], x, y);
			x = x + 80;
			j++;
		}
		y = y + 80;
		i++;
	}
}
