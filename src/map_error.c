/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:53:08 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:10:40 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Checks if the map is rectangular by comparing the length of each row */

static int	ft_map_is_rect(char **map)
{
	int	line;
	int	line_len;

	line = 0;
	line_len = ft_line_lenght(map[line]);
	if (line_len < 0)
		return (1);
	while (map[line])
	{
		if (ft_line_lenght(map[line]) != line_len)
			return (1);
		line++;
	}
	return (0);
}

/* Checks if the map is surrounded by walls ('1') */

static int	ft_map_walls(char **map)
{
	int	line;
	int	len;

	line = 0;
	len = ft_line_lenght(map[line]);
	while (map[line])
	{
		if (map[line][0] != '1' || map[line][len - 1] != '1')
			return (1);
		line++;
	}
	while (len - 1 > 0)
	{
		if (map[0][len - 1] != '1' || map[line - 1][len - 1] != '1')
			return (1);
		len--;
	}
	return (0);
}
/* Checks if there are 0 or more than one 'P' or 'E' in the map */

static int	ft_right_obj(char **map, char c)
{
	int	obj_count;

	obj_count = ft_get_object(map, c);
	if (obj_count == 0)
		return (1);
	if (obj_count > 1 && c != 'C')
		return (1);
	return (0);
}

/* Validates the path in the map using floodfill algorithm */

static int	ft_path_is_ok(t_data *game)
{
	char	**map_copy;
	t_pos	map_data;

	map_data.size_y = 0;
	while (game->map[map_data.size_y])
		map_data.size_y++;
	map_data.size_x = 0;
	if (game->map[0])
		map_data.size_x = ft_strlen(game->map[0]);
	map_copy = ft_copy_map(game->map);
	ft_find_player(map_copy, &map_data);
	ft_floodfill(map_copy, map_data, map_data.p_x, map_data.p_y);
	if (ft_check_floodfill(map_copy) == 1)
	{
		ft_free_map(map_copy);
		return (1);
	}
	ft_copy_player_pos(game, &map_data);
	ft_free_map(map_copy);
	return (0);
}

/* Checks for different errors in the map */

int	ft_map_is_error(t_data *game)
{
	int	i;

	i = 0;
	if (game->map[i] == NULL)
		return (ft_error_exit(EMPTY_MAP, game), 1);
	if (ft_map_is_rect(game->map) == 1)
		return (ft_error_exit(INVALID_MAP, game), 1);
	if (ft_map_walls(game->map) == 1)
		return (ft_error_exit(INVALID_WALLS, game), 1);
	if (ft_map_floor(game->map) == 1)
		return (ft_error_exit(INVALID_FLOOR, game), 1);
	if (ft_right_obj(game->map, 'P') == 1 || ft_right_obj(game->map, 'E') \
		|| ft_right_obj(game->map, 'C') == 1)
		return (ft_error_exit(INVALID_OBJECTS, game), 1);
	if (ft_path_is_ok(game) == 1)
		return (ft_error_exit(INVALID_PATH, game), 1);
	return (0);
}
