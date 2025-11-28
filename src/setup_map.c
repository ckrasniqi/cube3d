/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:52:02 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/28 20:28:54 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"


int	setup_game_variables(t_game *g, t_map_data *mdata, t_player player)
{
	int	prow;
	int	pcol;

	g->width = 1080;
	g->height = 720;
	g->tile_size = set_tile_size(mdata->map_cols, mdata->map_rows, \
			g->width, g->height);
	if (g->tile_size < 1)
		g->tile_size = 1;
	prow = player.py;
	pcol = player.px;
	if (prow >= 0 && pcol >= 0)
	{
		player.px = pcol * g->tile_size + g->tile_size / 2.0;
		player.py = prow * g->tile_size + g->tile_size / 2.0;
	}
	else
	{
		player.px = g->tile_size / 2.0;
		player.py = g->tile_size / 2.0;
	}
	player.move_speed = (double)g->tile_size * 0.5;
	g->last_time = get_time_seconds();
	return (1);
}

int	set_tile_size(int cols, int rows, int window_w, int window_h)
{
	int	tile_w;
	int	tile_h;

	if (cols <= 0 || rows <= 0)
		return (1);
	tile_w = window_w / cols;
	tile_h = window_h / rows;
	if (tile_w < tile_h)
		return (tile_w);
	return (tile_h);
}
