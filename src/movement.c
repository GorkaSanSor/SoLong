/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:03:34 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 10:31:49 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
This function checks if all the collectibles have been collected. If so, the
final door opens. Notice that we have to check before entering the Door square,
else we enter the Door square and we would need one more movement to close
the program
*/
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


/*
This function updates the player position with the help of the mlx library.
1. If the player collected a C, replace the char by 0, a FLOOR.
2. Update the count of C to check if the Exit should be unlocked
3. Replace the previous position of the player with the FLOOR.
4. If the player is on top of the Exit, put the exit after the player moves
5. Print the player in the new position 
Notice that x and y received is a memory address. We are using the content 
with *x and *y, and then sending the address to ft_print_player.
If the player moved to a tile with a C, it will be replaced by 0, to
count the remaining collectibles and unlock the final exit tile.
*/

static void	ft_move_player(t_data *game, int *x, int *y, char direction)
{
	int		img_width;
	int		img_height;
	void	*img;

	if (game->map[*y][*x] == 'C')
		game->map[*y][*x] = '0';
	ft_unlock_exit(game);
	if (game->map[*y][*x] == 'E' && ft_find_c(game->map) == 0)
		ft_exit_ok(game); // Cierra el programa si no quedan collectibles
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

/*
This function checks if the player reached a wall. Checks every direction
related to the key pressed and returns 0 or 1 depending on wheather the
movement was possible or not
*/

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

/*
This function gets the initial position of the player the first time it runs.
Step 1. Check if the player moved or not and returns if it did not.
Step 2. Check if the player reached the exit
Step 3. If it did not, move the player
*/

static int	ft_movement(t_data *game, char direction)
{
    static int  x;
    static int  y;

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

/*
This function records the keys pressed and moves the character.
Static variables are variables that retain their value between function calls,
so the first time the function is called, i is initialized to 0 and
subsequent calls will retain the previous value of i.
key codes correspond to specific keys on the keyboard, and they are usually
defined by the operating system.
Linux-Ubuntu
65361: left / 65362 up / 65363 right / 65364 down / 65307 ESC
The move flag determines if the player moved, by receiving a value from
ft_move, if so, it increases tha variable i.
*/

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
