/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:15:13 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 20:49:28 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	draw_wall(t_game *game, t_raycaster *rc,
	mlx_texture_t *tex, int x)
{
	int		y;
	int		tex_y;
	int		tex_x;
	double	step;
	double	tex_pos;

	tex_x = get_tex_x(rc, tex);
	step = 1.0 * tex->height / rc->lineHeight;
	tex_pos = (rc->drawStart - game->cfg.height / 2
			+ rc->lineHeight / 2) * step;
	y = rc->drawStart;
	if (rc->drawStart < 0)
		y = 0;
	if (rc->drawEnd > game->cfg.height)
		rc->drawEnd = game->cfg.height;
	while (y++ < rc->drawEnd)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= (int)tex->height)
			tex_y = tex->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		tex_pos += step;
		wall_texture(game, x, y, get_texture_pixel(tex, tex_x, tex_y));
	}
}

void	draw_sky(t_game *game, int end, int x)
{
	int			y;
	float		f;
	uint32_t	color;

	y = 0;
	while (y < end)
	{
		f = vignette_factor(x, y, &game->cfg, 0.65f);
		if (game->map_data.parsed_textures >= 5)
			color = get_texture_pixel(game->res.ceiling_texture, x, y);
		else
			color = game->map_data.ceiling_color;
		color = apply_mask(color, 10, f);
		mlx_put_pixel(game->res.image, x, y, color);
		y++;
	}
}

void	draw_floor(t_game *game, int x, int y)
{
	uint32_t	color;
	float		f;

	while (y++ < game->cfg.height)
	{
		f = vignette_factor(x, y, &game->cfg, 0.65f);
		color = apply_mask(game->map_data.floor_color, 10, f);
		mlx_put_pixel(game->res.image, x, y, color);
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
		draw_sky(game, end, x);
	}
	tex = get_texture(game, rc);
	draw_wall(game, rc, tex, x);
	y = rc->drawEnd;
	if (y < 0)
		y = 0;
	if (y > cfg->height)
		y = cfg->height;
	draw_floor(game, x, y);
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
	render_hand(game, 0);
}
