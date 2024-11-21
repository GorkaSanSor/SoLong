/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:44:46 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/21 11:52:26 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
This function loops every position of the 2D map with a double loop
and counts the number of occurrences of char c
i is the counter of rows.
j is the counter of colums (i.e., positions in every row)
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
	return (0);
}

/*
This function loops the copy of the map once it has been floodfilled. 
If it finds an E or C it means that the exit or a collectible was not reachable 
and thus calls the error function.
i is the counter of rows (Y)
j is the counter of colums (X)
*/

int	ft_check_floodfill(char **map_cpy)
{
	int	rows;
	int	cols;
	
	rows = 0;
	while (map_cpy[rows])
	{
		cols = 0;
		while (map_cpy[rows][cols] != '\0')
		{
			if (map_cpy[rows][cols] == 'C' || map_cpy[rows][cols] == 'E')
				return (1);
			cols++;
		}
		rows++;
	}
	return (0);
}

/*
This is the floodfill standard algorithm. It is a recursive method that fills
an area when the conditions are met. In this case, it will stop when it is
outside the size of the map (redundant, since map is surrounded by '1') or when
the position is a wall '1'. Every time it visits a position, it marks it as
'V' (visited), which is also a condition to stop filling.
*/

void	ft_fill(char **map_copy, t_pos map_data, int x, int y)
{
	if (x >= map_data.size_x || y >= map_data.size_y \
	|| map_copy[y][x] == '1' || map_copy[y][x] == 'V')
		return ;
	else
	{
		map_copy[y][x] = 'V';
		ft_fill(map_copy, map_data, x + 1, y);
		ft_fill(map_copy, map_data, x - 1, y);
		ft_fill(map_copy, map_data, x, y + 1);
		ft_fill(map_copy, map_data, x, y - 1);
	}
	return ;
}

/*
This function finds the initial position of the player and the size of
the map.
It just runs a regular loop, fixing the position of the current row y
and then loops all the positions of that row (columns x)
When it finds 'P' it saves the values of the player position in the struct
It continues reading all the map and then saves the size in the struct
*/


/*
This function makes a copy of the map. It is an array of pointers,
each pointer points to a string. The logic is similar to ft_split
i is the counter of the first level of pointers (or number of rows)
j is an aux counter to loop and save all the lines

i = 0		| * |			*| 1 |	| 1 |	| 1 |
i = 1		| * |			*| 1 |	| 1 |	| 1 |
...			| * |			*| 1 |	| 1 |	| 1 |
i = n		| * |			*| 1 |	| 1 |	| 1 |

First, allocate memory for the array of pointers
Second, loop and duplicate all the lines of the map (arrays of chars)
Place NULL at the end of the array of pointers
*/


