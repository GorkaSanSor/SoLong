/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:44:46 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/26 11:10:14 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
This function loops every position of the 2D map with a double loop
and counts the number of occurrences of char c
counter of rows.
counter of colums (i.e., positions in every row)
Loop the whole map at once until the final '\0'
*/

char	ft_get_object(char **map, char c)
{
	int rows;
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

/*
This function loops the copy of the map once it has been floodfilled. 
If it finds an E or C it means that the exit or a collectible was not reachable 
and thus calls the error function.
i is the counter of rows (Y)
j is the counter of colums (X)
*/

int ft_check_floodfill(char **map_copy) 
{
	int i;
	int j;

	i = 0;
	while (map_copy[i]) 
	{
		j = 0;
		while (map_copy[i][j] != '\0') 
		{
			// Revisa si la celda contiene un objeto (C o E)
			if (map_copy[i][j] == 'C' || map_copy[i][j] == 'E') 
			{
				ft_printf("Found object at (%d, %d)\n", i, j);  // Debugging
				return (1);  // Found the object
			}
			j++;
		}
		i++;
	}
	return (0);  // No object found
}


/*
This is the floodfill standard algorithm. It is a recursive method that fills
an area when the conditions are met. In this case, it will stop when it is
outside the size of the map (redundant, since map is surrounded by '1') or when
the position is a wall '1'. Every time it visits a position, it marks it as
'V' (visited), which is also a condition to stop filling.
*/

void ft_floodfill(char **map_copy, t_pos map_data, int x, int y)
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

/*
This function finds the initial position of the player and the size of
the map.
It just runs a regular loop, fixing the position of the current row y
and then loops all the positions of that row (columns x)
When it finds 'P' it saves the values of the player position in the struct
It continues reading all the map and then saves the size in the struct
*/

void	ft_find_player(char **map, t_pos *map_data)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while(map[y])
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

/*
This function makes a copy of the map. It is an array of pointers,
each pointer points to a string. The logic is similar to ft_split
rows is the counter of the first level of pointers (or number of rows)
i is an aux counter to loop and save all the lines

rows = 0		| * |			*| 1 |	| 1 |	| 1 |
rows = 1		| * |			*| 1 |	| 1 |	| 1 |
... 			| * |			*| 1 |	| 1 |	| 1 |
rows = n		| * |			*| 1 |	| 1 |	| 1 |

First, allocate memory for the array of pointers
Second, loop and duplicate all the lines of the map (arrays of chars)
Place NULL at the end of the array of pointers
*/

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
