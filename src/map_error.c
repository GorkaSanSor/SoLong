/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:53:08 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/21 12:03:00 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
This function compares the len of the first line of the map against further
reads. If any line has different len than the first one, it means the map is
not rectangular. ft_strlen has been modified to stop reading when a '\n' or
'\0' (EOF) is found.
*/

static int  ft_map_is_rect(char **map)
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

/*
If the map is surronunded by walls (char '1'). line is the counter for rows,
len is the counter for columns.
First part checks first and final columns.
		col 0					col len-1
row 0:	| 1 |					| 1 |
row 1:	| 1 |					| 1 |
...		| 1 |					| 1 |
...		| 1 |					| 1 |
row i:	| 1 |					| 1 |
After the first loop, the value i will be the number of rows
Second loop checks chars in the mid positions of first and last rows
row 0:			| 1 || 1 || 1 |
row 1:
...
...
row i:			| 1 || 1 || 1 |
*/

static int	ft_map_walls(char **map)
{
	int line;
	int len;
	
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
/*
This functions checks if there are 0 or more than one P or E in the map.
Several collectibles (C) are allowed
*/

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

/*
1. Create a copy of the map, in order not to modify the original map
2. Find the position of the player, it will be the start point
3. Floodfill algorithm in map_copy
4. Save the position of the player for later
Note that we send the address of the structure because it was created in 
this function
*/


/*
This function will check the different errors in the map
Function receives a pointer to make sure we are working on the original
structure and not in a local copy
Subject requirements:
Step 1. Map is not empty
Step 2. Map is a rectangle and must be surrounded by walls
Step 3. Check Player (P), Collectibles (C) and Exit (E)
Step 4. There must be a valid path to collect and exit
*/

int	ft_map_iserror(t_data *game)
{
	int i;

	i = 0;
	if (game->map[i] == NULL)
		return (ft_error_exit(EMPTY_MAP, game), 1);
	if (ft_map_is_rect(game->map) == 1)
		return (ft_error_exit(INVALID_MAP, game), 1);
	if (ft_map_walls(game->map) == 1)
		return (ft_error_exit(INVALID_WALLS, game), 1);
	if (ft_right_obj(game->map, 'P') == 1 || ft_right_obj(game->map, 'E') \
		|| ft_right_obj(game->map, 'C') == 1)
		return (ft_error_exit(INVALID_OBJECTS, game), 1);
	return (0);
}
