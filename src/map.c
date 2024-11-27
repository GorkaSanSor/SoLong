/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:18:47 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/27 12:12:40 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Returns the length of a line up to the newline character */

int	ft_line_lenght(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	return (i);
}
/* Saves the map from a file into the game structure */

void	ft_save_map(t_data *game, char *str)
{
	int		fd;
	char	*line;
	int		rows;

	rows = 0;
	fd = open(str, O_RDONLY);
	line = gnl(fd);
	while (line)
	{
		rows++;
		free(line);
		line = gnl(fd);
	}
	close(fd);
	game->map_rows = rows;
	game->map = ft_map_fill(&rows, str);
}
/* Fills the map array with lines from the file */

char	**ft_map_fill(int *rows, char *str)
{
	char	**map;
	int		row;
	int		fd;

	row = 0;
	fd = open(str, O_RDONLY);
	map = (char **)malloc((*rows + 1) * sizeof(char *));
	if (!map)
		return (0);
	while (row < *rows)
	{
		map[row] = gnl(fd);
		if (!map[row])
			ft_printf("Error reading line %d from the map\n", row);
		row++;
	}
	map[row] = NULL;
	close(fd);
	return (map);
}

/* Checks if the floor of the map contains only valid characters */

int	ft_map_floor(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == 'P' \
			|| map[i][j] == 'C' || map[i][j] == 'E' || map[i][j] == '\n')
				j++;
			else
				return (1);
		}
		i++;
	}
	return (0);
}
