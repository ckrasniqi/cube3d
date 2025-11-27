/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_keyhooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:25:51 by msalangi          #+#    #+#             */
/*   Updated: 2025/11/27 16:32:13 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

void	look_forward(t_game *game)
{
	double angle = game->map_data.player_start_angle;
}

void	look_back(t_game *game)
{
	double angle = game->map_data.player_start_angle;
	
}

void	look_right(t_game *game)
{
	double angle = game->map_data.player_start_angle;
	
}

void	look_left(t_game *game)
{
	double angle = game->map_data.player_start_angle;
	
}

void	arrow_hook(mlx_key_data_t keydata, void *g)
{
	t_game		*game = g;
	mlx_t		*mlx;

	mlx = game->mlx;
	if (!mlx || !game)
		return ;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		look_forward(game);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		look_back(game);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		look_left(game);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		look_right(game);
}
