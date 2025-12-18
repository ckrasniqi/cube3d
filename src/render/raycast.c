/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:15:13 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/17 22:32:13 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

mlx_texture_t	*get_texture(t_game *game, t_raycaster *rc)
{
	if (rc->side == 0)
	{
		if (rc->rayDirX > 0)
			return (game->res.wall_textures[TEX_EAST]);
		return (game->res.wall_textures[TEX_WEST]);
	}
	if (rc->rayDirY > 0)
		return (game->res.wall_textures[TEX_SOUTH]);
	return (game->res.wall_textures[TEX_NORTH]);
}

int	get_tex_x(t_raycaster *rc, mlx_texture_t *tex)
{
	int	tex_x;

	tex_x = (int)(rc->wallX * (double)tex->width);
	if ((rc->side == 0 && rc->rayDirX > 0)
		|| (rc->side == 1 && rc->rayDirY < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	draw_wall_texture(t_game *game, t_settings *cfg, t_raycaster *rc,
	mlx_texture_t *tex, int x)
{
	int		y;
	int		tex_y;
	int		tex_x;
	double	step;
	double	tex_pos;
	
	uint32_t	color;
	float dist = rc->perpWallDist;
	float light = get_light_factor(dist);

	tex_x = get_tex_x(rc, tex);
	step = 1.0 * tex->height / rc->lineHeight;
	tex_pos = (rc->drawStart - cfg->height / 2
		+ rc->lineHeight / 2) * step;
	y = rc->drawStart;
	if (rc->drawStart < 0)
		y = 0;
	if (rc->drawEnd > cfg->height)
		rc->drawEnd = cfg->height;
	while (y++ < rc->drawEnd)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		tex_pos += step;
		color = get_texture_pixel(tex, tex_x, tex_y);
		color = apply_mask(color, light);
		mlx_put_pixel(game->res.image, x, y,
			color);
	}
}

void	render_stripe(t_game *game, t_raycaster *rc, t_settings *cfg, int x)
{
	int				y;
	int				end;
	mlx_texture_t	*tex;

	y = 0;
	if (rc->drawStart > 0)
	{
		end = rc->drawStart;
		if (end > cfg->height)
			end = cfg->height;
		while (y < end)
		{
			if (game->map_data.parsed_textures >= 5)
				mlx_put_pixel(game->res.image, x, y,
					get_texture_pixel(game->res.ceiling_texture, x, y));
			else
				mlx_put_pixel(game->res.image, x, y,
					game->map_data.ceiling_color);
			y++;
		}
	}
	tex = get_texture(game, rc);
	draw_wall_texture(game, &game->cfg, rc, tex, x);
	y = rc->drawEnd;
	if (y < 0)
		y = 0;
	if (y > cfg->height)
		y = cfg->height;
	while (y++ < cfg->height)
		mlx_put_pixel(game->res.image, x, y, game->map_data.floor_color);
}

void	raycaster(t_game *game, t_raycaster *rc)
{
	int	x;

	x = 0;
	while (x < game->cfg.width)
	{
		rc->cameraX = 2 * x / (double)(game->cfg.width) - 1;
		rc->rayDirX = game->player.dirX + game->player.planeX * rc->cameraX;
		rc->rayDirY = game->player.dirY + game->player.planeY * rc->cameraX;
		init_raycaster_variables(game, rc);
		preform_dda(game, rc);
		calculate_wall_projection(game, rc);
		render_stripe(game, rc, &game->cfg, x);
		x++;
	}
}
