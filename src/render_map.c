/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:31:12 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/04 19:01:37 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	render_mini_map(t_game *game, t_map_data *m)
{
	int			mm_x;
	int			mm_y;
	int			tile;
	double		scale;
	int			margin;
	if (!game || !game->res.image)
		return (-1);
	scale = 0.25;
	margin = 20;
	tile = game->cfg.tile_size * scale;
	mm_x = game->cfg.width - (m->map_cols * tile) - margin;
	mm_y = margin;
	draw_minimap(game, mm_x, mm_y, tile, m);
	draw_grid2(game, mm_x, mm_y, tile, m);
	draw_player(game, mm_x, mm_y, tile, scale);
	raycaster(game, &game->raycast);
	return (0);
}

void	draw_minimap(t_game *game, int mm_x, int mm_y, int tile, t_map_data *m)
{
	int			x;
	int			y;
	uint32_t	color;

	y = -1;
	while (++y < m->map_rows)
	{
		x = -1;
		while (++x < m->map_cols)
		{
			if (m->map[y][x] == '1')
				color = 0x00008BFF;
			else
				color = 0xFFFFFFFF;
			draw_minimap_unit(game, mm_x + x * tile, mm_y + y * tile, tile, color);
		}
	}
}

void	draw_minimap_unit(t_game *game, int x, int y, int tile,  uint32_t color)
{
	int			i;
	int			j;

	i = -1;
	while (++i < tile)
	{
		j = -1;
		while (++j < tile)
			mlx_put_pixel(game->res.image, x + i, y + j, color);
	}
}

void draw_grid2(t_game *game, int mm_x, int mm_y, int tile, t_map_data *m)
{
	int	x;
	int	y;
	int	width;
	int	height;

	width = m->map_cols * tile;
	height = m->map_rows * tile;
	x = -1;
	while (++x <= width)
	{
		y = -1;
		while (++y <= height)
			mlx_put_pixel(game->res.image, mm_x + x, mm_y + y, 0x000000FF);
		x += tile - 1;
	}
	y = -1;
	while (++y <= height)
	{
		x = -1;
		while (++x <= width)
			mlx_put_pixel(game->res.image,mm_x + x, mm_y + y, 0x000000FF);
		y += tile - 1;
	}
}

void	draw_player(t_game *g, int mm_x, int mm_y, int tile, double scale)
{
	int		i;
	int		j;
	int		p_x;
	int		p_y;
	int 	size;

	size = tile / 3;
	p_x = mm_x + g->player.posX * scale;
	p_y = mm_y + g->player.posY * scale;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			mlx_put_pixel(g->res.image, p_x + i, p_y + j, 0x0DFF00FF);
	}
}
