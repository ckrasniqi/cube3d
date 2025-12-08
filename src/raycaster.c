/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:15:13 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/04 18:20:48 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	draw_vertical_line(t_game *game, t_raycaster *rc, t_settings *cfg, int x)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	uint32_t	color;

	lineHeight = abs((int)(cfg->height / ((rc->side == 0) ?
				(rc->mapX - rc->posX + (1 - rc->stepX) / 2) / rc->rayDirX :
				(rc->mapY - rc->posY + (1 - rc->stepY) / 2) / rc->rayDirY)));
	drawStart = -lineHeight / 2 + cfg->height / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + cfg->height / 2;
	if (drawEnd >= cfg->height)
		drawEnd = cfg->height - 1;
	color = (rc->side == 1) ? 0xFFAAAAAA : 0xFF777777;
	for (int y = drawStart; y < drawEnd; y++)
		mlx_put_pixel(game->res.image, x, y, color);
}

void	cast_single_ray(t_game *game, t_raycaster *rc, t_settings *cfg, int x)
{
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	if (rc->side == 0)
		perpWallDist = (rc->mapX - rc->posX + (1 - rc->stepX) / 2) / rc->rayDirX;
	else
		perpWallDist = (rc->mapY - rc->posY + (1 - rc->stepY) / 2) / rc->rayDirY;
	lineHeight = (int)(cfg->height / perpWallDist);
	drawStart = -lineHeight / 2 + cfg->height / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + cfg->height / 2;
	if (drawEnd >= cfg->height)
		drawEnd = cfg->height - 1;
	draw_vertical_line(game, rc, cfg, x);
}

void	raycaster(t_game *game, t_raycaster *rc)
{
	int	x;

	x = 0;
	init_raycaster_variables(game, rc, &game->cfg);
	while (x < game->cfg.width)
	{
		rc->cameraX = 2 * x / (double)(game->cfg.width) - 1;
		rc->rayDirX = game->player.dirX + game->player.planeX * rc->cameraX;
		rc->rayDirY = game->player.dirY + game->player.planeY * rc->cameraX;
		preform_dda(game, rc);
		cast_single_ray(game, rc, &game->cfg, x);
		x++;
	}
}
