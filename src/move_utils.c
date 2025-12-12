/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:49:53 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 18:52:56 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	collision_detection(t_game *g, double newPosX, double newPosY)
{
	int	mapX;
	int	mapY;

	mapX = (int)newPosX;
	mapY = (int)newPosY;

	if (mapX < 0 || mapX >= g->map_data.map_cols || \
		mapY < 0 || mapY >= g->map_data.map_rows)
		return (1);

	if (g->map_data.map[mapY][mapX] == '1')
		return (1);

	return (0);
}

void	attempt_move(t_game *g, double newX, double newY)
{
	if (!collision_detection(g, newX, g->player.posY))
		g->player.posX = newX;

	if (!collision_detection(g, g->player.posX, newY))
		g->player.posY = newY;
}
