/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:34:30 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/19 01:14:22 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	render_hand(t_game *game)
{
	int			x;
	int			y;
	uint32_t	color;
	float		f;
	
	x = 0;
	y = 0;
	while (x < 640)
	{
		while (y < 640)
		{
			color = get_texture_pixel(game->res.left_hand, x, y);
			if (color != 0x000000FF)
			{
				f = vignette_factor(480 + x, 280 + y, game->cfg.width, game->cfg.height, 0.65f);
				color = apply_mask(color, 10, f);
				mlx_put_pixel(game->res.image, 500 + x, 280 + y, color);
			}
			y++;
		}
		y = 0;
		x++;
	}
}
