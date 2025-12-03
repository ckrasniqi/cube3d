/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:15:13 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/03 17:18:52 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	raycaster(t_game *game, t_raycaster *rc, double rayDirX, double rayDirY)
{
	int	x;

	x = 0;
	(void)rayDirX;
	(void)rayDirY;

	while (x < game->cfg.width)
	{
		rc->cameraX = 2 * x / (double)(game->cfg.width) - 1;
		rc->rayDirX = game->player.dirX + game->player.planeX * rc->cameraX;
		rc->rayDirY = game->player.dirY + game->player.planeY * rc->cameraX;
		rc->mapX = (int)(game->player.posX / game->cfg.tile_size);
		rc->mapY = (int)(game->player.posY / game->cfg.tile_size);

		cast_single_ray(game);
		x++;
	}
}
void	cast_single_ray(t_game *game)
{
	// Raycasting logic to be implemented here
	(void)game;
}
