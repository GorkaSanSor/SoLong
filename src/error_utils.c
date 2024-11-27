/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:44:46 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:22:58 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Counts the number of occurrences of character c in the 2D map. */

char	ft_get_object(char **map, char c)
{
	int	rows;
	int	cols;
	int	count;

	rows = 0;
	count = 0;
	while (map[rows])
	{
		cols = 0;
		while (map[rows][cols] != '\0')
		{
			if (map[rows][cols] == c)
				count++;
			cols++;
		}
		rows++;
	}
	return (count);
}

/* Checks if the floodfilled map still contains 'E' or 'C'. */
int	ft_check_floodfill(char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j] != '\0')
		{
			if (map_copy[i][j] == 'C' || map_copy[i][j] == 'E')
			{
				ft_printf("Found object at (%d, %d)\n", i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/* Implements the floodfill algorithm to fill an area. */

void	ft_floodfill(char **map_copy, t_pos map_data, int x, int y)
{
	if (x < 0 || y < 0 || x >= map_data.size_x || y >= map_data.size_y)
		return ;
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return ;
	map_copy[y][x] = 'V';
	ft_floodfill(map_copy, map_data, x + 1, y);
	ft_floodfill(map_copy, map_data, x - 1, y);
	ft_floodfill(map_copy, map_data, x, y + 1);
	ft_floodfill(map_copy, map_data, x, y - 1);
}

/* Finds the initial position of the player and the size of the map. */

void	ft_find_player(char **map, t_pos *map_data)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'P')
			{
				map_data->p_x = x;
				map_data->p_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
	map_data->p_x = x;
	map_data->p_y = y;
	return ;
}

/* Creates a copy of the map. */

char	**ft_copy_map(char **map)
{
	char	**map_copy;
	int		i;
	int		rows;

	if (!map)
		return (NULL);
	rows = 0;
	while (map[rows])
		rows++;
	map_copy = malloc((rows + 1) * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			ft_free_map(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
