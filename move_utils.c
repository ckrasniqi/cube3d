/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:29:08 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/29 20:29:54 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	collision_detection(t_game *g, double newPosX, double newPosY)
{
	int	tile = g->cfg.tile_size;
	int	mapX = (int)(newPosX / tile);
	int	mapY = (int)(newPosY / tile);

	if (mapX < 0 || mapX >= g->map_data.map_cols || mapY < 0 || mapY >= g->map_data.map_rows)
		return (1);
	if (g->map_data.map[mapY][mapX] == '1')
		return (1);
	return (0);
}

void move_down(t_game *g, double dirX, double dirY, double move_step)
{
	double	newPosX;
	double	newPosY;

	newPosX = g->player.posX - dirX * move_step;
	newPosY = g->player.posY - dirY * move_step;
	if (collision_detection(g, newPosX, newPosY))
		return ;
	g->player.posX = newPosX;
	g->player.posY = newPosY;
	render_mini_map(g, &g->map_data);
}

void	move_left(t_game *g, double dirX, double dirY, double move_step)
{
	double	newPosX;
	double	newPosY;

	newPosX = g->player.posX - dirY * move_step;
	newPosY = g->player.posY + dirX * move_step;
	if (collision_detection(g, newPosX, newPosY))
		return ;
	g->player.posX = newPosX;
	g->player.posY = newPosY;
	render_mini_map(g, &g->map_data);
}

void	move_right(t_game *g, double dirX, double dirY, double move_step)
{
	double	newPosX;
	double	newPosY;

	newPosX = g->player.posX + dirY * move_step;
	newPosY = g->player.posY - dirX * move_step;
	if (collision_detection(g, newPosX, newPosY))
		return ;
	g->player.posX = newPosX;
	g->player.posY = newPosY;
	render_mini_map(g, &g->map_data);
}

void	move_up(t_game *g, double dirX, double dirY, double move_step)
{
	double	newPosX;
	double	newPosY;

	newPosX = g->player.posX + dirX * move_step;
	newPosY = g->player.posY + dirY * move_step;
	if (collision_detection(g, newPosX, newPosY))
		return ;
	g->player.posX = newPosX;
	g->player.posY = newPosY;
	render_mini_map(g, &g->map_data);
}
