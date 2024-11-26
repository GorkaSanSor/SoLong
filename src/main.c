/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:05:20 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/26 12:21:53 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_init_struct(t_data *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->map = NULL;
	game->map_rows = 0;
	game->p_x_copy = 0;
	game->p_y_copy = 0;
	game->final_move = 0;
}

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

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc == 2)
	{
		ft_init_struct(&game);
		if (ft_check_extension(&game, argv[1]) == 1)
			return (1);
		ft_save_map(&game, argv[1]);
		if (ft_map_is_error(&game) == 1)
			return (1);
		ft_init_game(&game);
	}
	ft_error_exit(WRONG_ARGS, &game);
	ft_exit_ok(&game);
	return (0);
}
