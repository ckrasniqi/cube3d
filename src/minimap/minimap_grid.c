/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:16:27 by msalangi          #+#    #+#             */
/*   Updated: 2025/11/27 16:02:01 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"
#define BLACK 0x00000000
// 		y
//		| [unit_s] border	
// x -- *---------------------*	width = unit_s * cols
// 		*                     *
// 		*                     *
// 		*                     *
// 		*                     *  
// 		*                     *
// 		*                     * 
// 		*                     *
// 		*---------------------*  height = unit_s * rows
//[unit_s] border

int	draw_grid(t_map_data map_data, t_game *game)
{
	int	x;
	int y;

	// x = UNIT_S;
	// y = UNIT_S;
	x = 0;
	y = 0;
	int width = UNIT_S * (map_data.map_cols + 1);
	int height = UNIT_S * (map_data.map_rows + 1);
	
	while (x <= width)
	{
		while (y <= height)
		{
			mlx_put_pixel(game->image, x, y, BLACK);
			y++;
		}
		// y = UNIT_S;
		y = 0;
		x += UNIT_S;
	}
	draw_rows(map_data, game);
	return (0);
}

int	draw_rows(t_map_data map_data, t_game *game)
{
	int	x;
	int y;

	// x = UNIT_S;
	// y = UNIT_S;
	x = 0;
	y = 0;
	int width = UNIT_S * (map_data.map_cols + 1);
	int height = UNIT_S * (map_data.map_rows + 1);
	
	while (y <= width)
	{
		while (x <= height)
		{
			mlx_put_pixel(game->image, x, y, BLACK);
			x++;
		}
		x = 0;
		// x = UNIT_S;
		y += UNIT_S;
	}
	return (0);
}