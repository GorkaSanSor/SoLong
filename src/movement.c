/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:03:34 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:08:22 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Unlocks the exit if all collectibles are collected */
static void	ft_unlock_exit(t_data *game)
{
	int		i;
	int		j;
	void	*img;
	int		img_width;
	int		img_height;

	if (ft_find_c(game->map) == 0)
	{
		img = mlx_xpm_file_to_image(game->mlx, EXIT_O, &img_width, &img_height);
		j = -1;
		while (game->map[++j])
		{
			i = -1;
			while (game->map[j][++i])
				if (game->map[j][i] == 'E')
					mlx_put_image_to_window(game->mlx, game->window, img, \
					(i * 80), (j * 80));
		}
	}
}
/* Updates the player's position and checks for collectibles or exit */

static void	ft_move_player(t_data *game, int *x, int *y, char direction)
{
	int		img_width;
	int		img_height;
	void	*img;

	if (game->map[*y][*x] == 'C')
		game->map[*y][*x] = '0';
	ft_unlock_exit(game);
	if (game->map[*y][*x] == 'E' && ft_find_c(game->map) == 0)
		ft_exit_ok(game);
	img = mlx_xpm_file_to_image(game->mlx, FLOOR, &img_width, &img_height);
	mlx_put_image_to_window(game->mlx, game->window, img, (*x * 80), (*y * 80));
	if (game->map[*y][*x] == 'E')
	{
		img = mlx_xpm_file_to_image(game->mlx, EXIT, &img_width, &img_height);
		mlx_put_image_to_window(game->mlx, game->window, img, (*x * 80), \
		(*y * 80));
	}
	ft_print_player(game, x, y, direction);
}

/* Checks if the player movement is blocked by a wall */

static int	ft_player_stop(t_data *game, int x, int y, char direction)
{
	if (direction == 'U')
	{
		if (game->map[y - 1][x] == '1')
			return (1);
	}
	if (direction == 'D')
	{
		if (game->map[y + 1][x] == '1')
			return (1);
	}
	if (direction == 'L')
	{
		if (game->map[y][x - 1] == '1')
			return (1);
	}
	if (direction == 'R')
	{
		if (game->map[y][x + 1] == '1')
			return (1);
	}
	return (0);
}
/* Handles player movement based on direction */

static int	ft_movement(t_data *game, char direction)
{
	static int	x;
	static int	y;

	if (!x && !y)
	{
		x = game->p_x_copy;
		y = game->p_y_copy;
	}
	if (!direction)
		return (0);
	if (ft_player_stop(game, x, y, direction) == 1)
		return (0);
	ft_move_player(game, &x, &y, direction);
	return (1);
}
/* Processes input keys and moves the player accordingly */

int	ft_input(int key, t_data *game)
{
	static int	i;
	int			move_flag;

	if (!i)
		i = 0;
	move_flag = 0;
	if (key == XK_Escape)
		ft_exit_ok(game);
	if (key == XK_Left || key == XK_a)
		move_flag = ft_movement(game, 'L');
	if (key == XK_Right || key == XK_d)
		move_flag = ft_movement(game, 'R');
	if (key == XK_Down || key == XK_s)
		move_flag = ft_movement(game, 'D');
	if (key == XK_Up || key == XK_w)
		move_flag = ft_movement(game, 'U');
	if (move_flag == 1)
	{
		i++;
		game->final_move = i + 1;
		ft_printf("Movement #: |%d|\n", i);
	}
	return (0);
}
