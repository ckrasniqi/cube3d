/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:13:11 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/20 23:27:22 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

mlx_texture_t	*get_texture(t_game *game, t_raycaster *rc)
{
	if (rc->side == 0)
	{
		if (rc->ray_dir_x > 0)
			return (game->res.wall_textures[TEX_EAST]);
		return (game->res.wall_textures[TEX_WEST]);
	}
	if (rc->ray_dir_y > 0)
		return (game->res.wall_textures[TEX_SOUTH]);
	return (game->res.wall_textures[TEX_NORTH]);
}

int	get_tex_x(t_raycaster *rc, mlx_texture_t *tex)
{
	int	tex_x;

	tex_x = (int)(rc->wall_x * (double)tex->width);
	if ((rc->side == 0 && rc->ray_dir_x > 0)
		|| (rc->side == 1 && rc->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

void	wall_texture(t_game *game, int x, int y, uint32_t color)
{
	if (!check_yellow(color))
		color = apply_mask(color, get_light_factor(game->raycast.perp_wall_dist),
				vignette_factor(x, y, &game->cfg, 0.65f));
	mlx_put_pixel(game->res.image, x, y, color);
}
