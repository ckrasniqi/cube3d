/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:33:09 by msalangi          #+#    #+#             */
/*   Updated: 2025/11/27 16:39:42 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// find player position based on known .cub position * unit_s

#include "../../include/cube3d.h"

void	find_player(t_game *game)
{
	int location[2];
	location[0] = game->map_data.player_position_cub[0];
	location[1] = game->map_data.player_position_cub[1];

	printf("\nplayer is: %i, %i\n", location[0], location[1]);
}
