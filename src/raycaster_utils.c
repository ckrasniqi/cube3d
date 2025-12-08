/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:18:10 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/03 19:19:07 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	preform_dda(t_game *game, t_raycaster *rc)
{
	while (rc->hit == 0)
	{
		if (rc->sideDistX < rc->sideDistY)
		{
			rc->sideDistX += rc->deltaDistX;
			rc->mapX += rc->stepX;
			rc->side = 0;
		}
		else
		{
			rc->sideDistY += rc->deltaDistY;
			rc->mapY += rc->stepY;
			rc->side = 1;
		}
		if (game->map_data.map[rc->mapY][rc->mapX] == '1')
			rc->hit = 1;
	}
}

double	find_delta_dist(double rayDir)
{
	if (rayDir == 0)
		return (1e30);
	return (fabs(1.0 / rayDir));
}

void	calculate_step_and_side_dist(t_raycaster *rc)
{
	if (rc->rayDirX < 0)
	{
		rc->stepX = -1;
		rc->sideDistX = (rc->posX - rc->mapX) * rc->deltaDistX;
	}
	else
	{
		rc->stepX = 1;
		rc->sideDistX = (rc->mapX + 1.0 - rc->posX) * rc->deltaDistX;
	}
	if (rc->rayDirY < 0)
	{
		rc->stepY = -1;
		rc->sideDistY = (rc->posY - rc->mapY) * rc->deltaDistY;
	}
	else
	{
		rc->stepY = 1;
		rc->sideDistY = (rc->mapY + 1.0 - rc->posY) * rc->deltaDistY;
	}
}

void	init_raycaster_variables(t_game *game, t_raycaster *rc, t_settings *cfg)
{
	int tile;

	tile = cfg->tile_size;
	rc->posX = game->player.posX / (double)tile;
	rc->posY = game->player.posY / (double)tile;
	rc->mapX = (int)rc->posX;
	rc->mapY = (int)rc->posY;
	rc->deltaDistX = find_delta_dist(rc->rayDirX);
	rc->deltaDistY = find_delta_dist(rc->rayDirY);
	calculate_step_and_side_dist(rc);
}
