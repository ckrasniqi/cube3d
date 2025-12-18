/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:49:53 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/17 21:01:20 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	collision_detection(t_game *g, double newPosX, double newPosY)
{
	int	map_x;
	int	map_y;

	map_x = (int)newPosX;
	map_y = (int)newPosY;
	if (map_x < 0 || map_x >= g->map_data.map_cols ||
		map_y < 0 || map_y >= g->map_data.map_rows)
		return (1);
	if (g->map_data.map[map_y][map_x] == '1')
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
