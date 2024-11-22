/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsantill <gsantill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:22:39 by gsantill          #+#    #+#             */
/*   Updated: 2024/11/22 10:42:12 by gsantill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
This function chooses the corresponding image of the player depending on the
key that has been pressed. xpm_path is initialized to NULL to avoid an error
on the compiler saying that xpm_path "might not be initialized" in all the
cases
*/


/*
This function prints the player after it has moved. Depending on the direction
it prints the corresponding XPM image. Notice that x and y received are
memory addresses
*/


/*
This function gets the position of the player in the map. It then updats the
coordinates in the map_data struct and copies them to the game struct
*/

void	ft_copy_player_pos(t_data *game, t_pos *map_data)
{
	game->p_x_copy = map_data->p_x;
	game->p_x_copy = map_data->p_y;
}

/*
Scans the map to check if there are still collectibles left
*/