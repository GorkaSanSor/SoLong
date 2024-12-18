/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:05:20 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:39:31 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Initializes the game structure to default values */
static void	ft_init_struct(t_data *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->map = NULL;
	game->textures.wall = NULL;
	game->textures.floor = NULL;
	game->textures.collectible = NULL;
	game->textures.exit = NULL;
	game->textures.player_u = NULL;
	game->textures.player_d = NULL;
	game->textures.player_l = NULL;
	game->textures.player_r = NULL;
	game->map_rows = 0;
	game->p_x_copy = 0;
	game->p_y_copy = 0;
	game->final_move = 0;
}

/* Initializes the game, creating the window and setting up hooks */
static void	ft_init_game(t_data *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, (ft_line_lenght(game->map[0]) \
	* 80), ((game->map_rows) * 80), "Hold the BTCs!");
	ft_scan_map(game);
	mlx_key_hook(game->window, *ft_input, game);
	mlx_hook(game->window, 17, 1L << 17, ft_exit_ok, game);
	mlx_loop(game->mlx);
}

/* Cleans up and frees all allocated resources */
void	ft_cleanup(t_data *game)
{
	if (game->map)
		ft_free_map(game->map);
	if (game->mlx && game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

/* Main function to initialize, run, and cleanup the game */
int	main(int argc, char **argv)
{
	t_data	game;

	if (argc == 2)
	{
		ft_init_struct(&game);
		if (ft_check_extension(&game, argv[1]) == 1)
		{
			ft_cleanup(&game);
			return (1);
		}
		ft_save_map(&game, argv[1]);
		if (ft_map_is_error(&game) == 1)
		{
			ft_cleanup(&game);
			return (1);
		}
		ft_init_game(&game);
	}
	else
	{
		ft_error_exit(WRONG_ARGS, &game);
	}
	ft_cleanup(&game);
	ft_exit_ok(&game);
	return (0);
}
