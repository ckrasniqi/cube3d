/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:31:12 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/28 21:00:20 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	render_mini_map(t_game *game, t_map_data *m)
{
	if (!game || !game->image)
		return (-1);

	draw_map(game, m);
	draw_grid2(game);
	draw_player(game);
}

void	draw_map(t_game *game, t_map_data *m)
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
			draw_map_unit(game, x * game->tile_size,\
					y * game->tile_size, color);
		}
	}
}

void	draw_map_unit(t_game *game, int x, int y, uint32_t color)
{
	int			i;
	int			j;

	i = -1;
	while (++i < game->tile_size)
	{
		j = -1;
		while (++j < game->tile_size)
			mlx_put_pixel(game->image, x + i, y + j, color);
	}
}

void draw_grid2(t_game *game)
{
	int	x;
	int	y;

	if (!game || game->tile_size <= 0)
		return;
	x = -1;
	while (++x < game->width)
	{
		y = -1;
		while (++y < game->height)
			mlx_put_pixel(game->image, x, y, 0x00FF00FF);
		x += game->tile_size;
	}
	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
			mlx_put_pixel(game->image, x, y, 0x00FF00FF);
		y += game->tile_size;
	}
}

void	draw_player(t_game *g)
{
	int		i;
	int		j;
	int		player_x;
	int		player_y;

	player_x = (int)g->player.px;
	player_y = (int)g->player.py;
	i = -1;
	while (++i < g->tile_size / 3)
	{
		j = -1;
		while (++j < g->tile_size / 3)
			mlx_put_pixel(g->image, player_x - (g->tile_size / 6) + i, \
					player_y - (g->tile_size / 6) + j, 0x00FF00FF);
	}
}
