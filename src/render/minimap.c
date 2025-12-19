/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:31:12 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/19 01:04:35 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	draw_minimap_square(t_game *game, int x, int y,
	int size, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
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

	p_screen_x = mm_x + (int)(game->player.posX * tile_size);
	p_screen_y = mm_y + (int)(game->player.posY * tile_size);
	draw_minimap_square(game, p_screen_x - 2, p_screen_y - 2, 4, RED);
}

int	render_mini_map(t_game *game, t_map_data *m)
{
	int			mm_x;
	int			mm_y;
	int			x;
	int			y;
	uint32_t	color;

	mm_x = game->cfg.width - (m->map_cols * 12) - 10;
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
			draw_minimap_square(game, mm_x + x * 12, \
				mm_y + y * 12, 11, color);
		}
	}
	draw_minimap_player(game, mm_x, mm_y, 12);
	return (0);
}
