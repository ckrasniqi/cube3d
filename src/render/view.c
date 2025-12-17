/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:52:02 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/17 15:37:27 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	setup_game_variables(t_game *g, t_map_data *mdata, t_player *player)
{
	g->cfg.width = 1080;
	g->cfg.height = HEIGHT;
	g->cfg.tile_size = set_tile_size(mdata->map_cols, mdata->map_rows, \
									g->cfg.width / 3, g->cfg.height / 3);
	if (player->posY >= 0 && player->posX >= 0)
	{
		player->posX = (double)player->posX + 0.5;
		player->posY = (double)player->posY + 0.5;
	}
	else
	{
		player->posX = 2.5;
		player->posY = 2.5;
	}
	player->move_speed = 0.05;
	player->rot_speed = 0.03;
	g->time.last = get_time_seconds();
}

int	set_tile_size(int cols, int rows, int window_w, int window_h)
{
	int	tile_w;
	int	tile_h;

	if (cols <= 0 || rows <= 0)
		return (10);
	tile_w = window_w / cols;
	tile_h = window_h / rows;
	if (tile_w < tile_h)
		return (tile_w);
	return (tile_h);
}
