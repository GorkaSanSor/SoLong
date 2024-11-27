/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:58:54 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 09:54:19 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Checks if map extension is .ber*/
int	ft_check_extension(t_data *game, char *str)
{
	int i;
	
	i = 0;
	while (str[i])
		i++;
	if (str[i - 4] != '.' || str[i - 3] != 'b' || str[i - 2] != 'e' \
	|| str[i - 1] != 'r')
	{
		ft_error_exit(WRONG_EXT, game);
		return (1);
	}
	return (0);
}

void	ft_free_map(char **map)
{
	int i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	ft_game_free(t_data *game)
{
	if (game->map)
		ft_free_map(game->map);
	if (game->mlx)
	{
		ft_free_textures(game);
		free(game->mlx);
		game->mlx = NULL;
	}
}
int	ft_exit_ok(t_data *game)
{
	if (game->mlx && game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		game->mlx = NULL;
	}
	ft_game_free(game);
	exit(0);
	return (0);
}
/*
This function will free all the memory and exit the program in error -1
Before exiting, it will free all the allocated memory
We need t_data *game to delete the original variable, not a local copy.
There is a special case, if WRONG_ARGS, game was not created so no need to 
call ft_general_free()
*/

void	ft_error_exit(int err_type, t_data *game)
{
	if (err_type == WRONG_ARGS)
		ft_printf("Error\nWrong number of arguments.|n"), exit(1);
	if (err_type == WRONG_EXT)
		ft_printf("Error\nInvalid map, there is not an exit.\n"), exit(1);
	if (err_type == EMPTY_MAP)
		ft_game_free(game), ft_printf("Error\nInvalid map, \
it`s empty.\n"), exit(1);
	if (err_type == INVALID_MAP)
		ft_game_free(game), ft_printf("Error\nInvalid map, \
must be rectangle.\n"), exit(1);
	if (err_type == INVALID_WALLS)
		ft_game_free(game), ft_printf("Error\nInvalid map, \
must be surrounded by walls.\n"), exit(1);
	if (err_type == INVALID_FLOOR)
		ft_game_free(game), ft_printf("Error\nInvalid map, \
the floor must be '0'.\n"), exit(1);
	if (err_type == INVALID_OBJECTS)
		ft_game_free(game), ft_printf("Error\nInvalid object type or \
	number. Allowed types and count: P = 1, E = 1, C >= 1\n"), exit(1);
	if (err_type == INVALID_PATH)
		ft_game_free(game), ft_printf("Error\nInvalid path.\n"), exit(1);
	if (err_type == INVALID_XPM)
		ft_game_free(game), ft_printf("Error\nXPM file not found.\n"), exit(1);
}

