/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:18:10 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 19:27:41 by ckrasniq         ###   ########.fr       */
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

void	calculate_wall_projection(t_game *game, t_raycaster *rc)
{

	if (rc->side == 0)
		rc->perpWallDist = (rc->sideDistX - rc->deltaDistX);
	else
		rc->perpWallDist = (rc->sideDistY - rc->deltaDistY);

	if (rc->perpWallDist < 0.0001)
		rc->perpWallDist = 0.0001;
	rc->lineHeight = (int)(game->cfg.height / rc->perpWallDist);

	rc->drawStart = -rc->lineHeight / 2 + game->cfg.height / 2;
	if (rc->drawStart < 0)
		rc->drawStart = 0;

	rc->drawEnd = rc->lineHeight / 2 + game->cfg.height / 2;
	if (rc->drawEnd >= game->cfg.height)
		rc->drawEnd = game->cfg.height - 1;

	if (rc->side == 0)
		rc->wallX = rc->posY + rc->perpWallDist * rc->rayDirY;
	else
		rc->wallX = rc->posX + rc->perpWallDist * rc->rayDirX;

	rc->wallX -= floor(rc->wallX);

}

void	init_raycaster_variables(t_game *game, t_raycaster *rc)
{
	rc->posX = game->player.posX;
	rc->posY = game->player.posY;
	rc->mapX = (int)rc->posX;
	rc->mapY = (int)rc->posY;
	rc->hit = 0;
	rc->side = 0;
	rc->perpWallDist = 0.0;
	rc->deltaDistX = find_delta_dist(rc->rayDirX);
	rc->deltaDistY = find_delta_dist(rc->rayDirY);
	calculate_step_and_side_dist(rc);
}
