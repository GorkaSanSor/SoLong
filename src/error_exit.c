/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:58:54 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:38:01 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Checks if the map file has a .ber extension */
int	ft_check_extension(t_data *game, char *str)
{
	int	i;

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

/* Frees the memory allocated for the map */
void	ft_free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/* Frees game resources */
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

/* Exits the game cleanly, freeing all resources */
int	ft_exit_ok(t_data *game)
{
	ft_cleanup(game);
	exit(0);
	return (0);
}
/* Exits the game with an error message, freeing all resources */

void	ft_error_exit(int err_type, t_data *game)
{
	if (err_type == WRONG_ARGS)
		return (ft_printf("Error\nWrong number of arguments.|n"), exit(1));
	if (err_type == WRONG_EXT)
		return (ft_printf("Error\nMap error, there's not an exit.\n"), exit(1));
	if (err_type == EMPTY_MAP)
		return (ft_game_free(game), ft_printf("Error\nInvalid map, \
it`s empty.\n"), exit(1));
	if (err_type == INVALID_MAP)
		return (ft_game_free(game), ft_printf("Error\nInvalid map, \
must be rectangle.\n"), exit(1));
	if (err_type == INVALID_WALLS)
		return (ft_game_free(game), ft_printf("Error\nInvalid map, \
must be surrounded by walls.\n"), exit(1));
	if (err_type == INVALID_FLOOR)
		return (ft_game_free(game), ft_printf("Error\nInvalid map, \
the floor must be '0'.\n"), exit(1));
	if (err_type == INVALID_OBJECTS)
		return (ft_game_free(game), ft_printf("Error\nInvalid object type or \
	number. Allowed types and count: P = 1, E = 1, C >= 1\n"), exit(1));
	if (err_type == INVALID_PATH)
		return (ft_game_free(game), ft_printf("Path error.\n"), exit(1));
	if (err_type == INVALID_XPM)
		return (ft_game_free(game), ft_printf("Error\nXPM file not \
		found.\n"), exit(1));
	ft_cleanup(game);
}
