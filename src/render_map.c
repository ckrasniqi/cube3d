/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:31:12 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/03 17:06:44 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	render_mini_map(t_game *game, t_map_data *m)
{
	if (!game || !game->res.image)
		return (-1);
	draw_map(game, m);
	draw_grid2(game);
	draw_player(game);
	raycaster(game, &game->raycast, game->raycast.rayDirX, game->raycast.rayDirY);
	return (0);
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
			draw_map_unit(game, x * game->cfg.tile_size,\
					y * game->cfg.tile_size, color);
		}
	}
}

void	draw_map_unit(t_game *game, int x, int y, uint32_t color)
{
	int			i;
	int			j;

	i = -1;
	while (++i < game->cfg.tile_size)
	{
		j = -1;
		while (++j < game->cfg.tile_size)
			mlx_put_pixel(game->res.image, x + i, y + j, color);
	}
}

void draw_grid2(t_game *game)
{
	int	x;
	int	y;

	if (!game || game->cfg.tile_size <= 0)
		return;
	x = -1;
	while (++x < game->cfg.width)
	{
		y = -1;
		while (++y < game->cfg.height)
			mlx_put_pixel(game->res.image, x, y, 0x00FF00FF);
		x += game->cfg.tile_size - 1;
	}
	y = -1;
	while (++y < game->cfg.height)
	{
		x = -1;
		while (++x < game->cfg.width)
			mlx_put_pixel(game->res.image, x, y, 0x00FF00FF);
		y += game->cfg.tile_size - 1;
	}
}

void	draw_player(t_game *g)
{
	int		i;
	int		j;
	int		player_x;
	int		player_y;

	player_x = (int)g->player.posX;
	player_y = (int)g->player.posY;
	i = -1;
	while (++i < g->cfg.tile_size / 3)
	{
		j = -1;
		while (++j < g->cfg.tile_size / 3)
			mlx_put_pixel(g->res.image, player_x - (g->cfg.tile_size / 6) + i, \
					player_y - (g->cfg.tile_size / 6) + j, 0x00FF00FF);
	}
}
