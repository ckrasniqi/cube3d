/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:52:02 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/04 18:29:18 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"


int	setup_game_variables(t_game *g, t_map_data *mdata, t_player *player)
{
	int	prow;
	int	pcol;
	(void)mdata;
	g->cfg.width = 720;
	g->cfg.height = 720;
	g->cfg.tile_size = set_tile_size(mdata->map_cols, \
			mdata->map_rows, g->cfg.width, g->cfg.height);
	if (g->cfg.tile_size < 1)
		g->cfg.tile_size = 1;
	prow = player->posY;
	pcol = player->posX;
	if (prow >= 0 && pcol >= 0)
	{
		player->posX = pcol * g->cfg.tile_size + g->cfg.tile_size / 2.0;
		player->posY = prow * g->cfg.tile_size + g->cfg.tile_size / 2.0;
	}
	player->move_speed = (double)g->cfg.tile_size * 0.5;
	g->time.last = get_time_seconds();
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
