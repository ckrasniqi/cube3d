/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:59:59 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:29:03 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	rotate_player(t_player *p, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
}

void	handle_rotation(t_game *game, double rot_speed)
{
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_LEFT))
		rotate_player(&game->player, -rot_speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_RIGHT))
		rotate_player(&game->player, rot_speed);
}

void	handle_movement(t_game *game, double dir_x, double dir_y)
{
	double	speed;

	speed = game->player.move_speed;
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_W))
		move_up(game, dir_x, dir_y, speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_S))
		move_down(game, dir_x, dir_y, speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_A))
		move_left(game, dir_x, dir_y, speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_D))
		move_right(game, dir_x, dir_y, speed);
}
