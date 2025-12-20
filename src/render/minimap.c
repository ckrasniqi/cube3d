/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:31:12 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:26:44 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	draw_minimap_square(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	if (color == RED)
		size = 4;
	else
		size = 10;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (x + i >= 0 && x + i < game->cfg.width && \
				y + j >= 0 && y + j < game->cfg.height)
				mlx_put_pixel(game->res.image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_game *game, int mm_x, int mm_y, int tile_size)
{
	int	p_screen_x;
	int	p_screen_y;

	p_screen_x = mm_x + (int)(game->player.pos_x * tile_size);
	p_screen_y = mm_y + (int)(game->player.pos_y * tile_size);
	draw_minimap_square(game, p_screen_x - 2, p_screen_y - 2, RED);
}

int	render_mini_map(t_game *game, t_map_data *m)
{
	int			mm_x;
	int			mm_y;
	int			x;
	int			y;
	uint32_t	color;

	mm_x = game->cfg.width - (m->map_cols * 10) - 10;
	mm_y = 10;
	y = -1;
	while (++y < m->map_rows)
	{
		x = -1;
		while (++x < m->map_cols)
		{
			if (m->map[y][x] == '1')
				color = GRAY;
			else
				color = YELLOW;
			draw_minimap_square(game, mm_x + x * 10,
				mm_y + y * 10, color);
		}
	}
	draw_minimap_player(game, mm_x, mm_y, 10);
	return (0);
}
