/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:59:59 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 19:01:55 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	rotate_player(t_player *p, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dirX;
	p->dirX = p->dirX * cos(rot_speed) - p->dirY * sin(rot_speed);
	p->dirY = old_dir_x * sin(rot_speed) + p->dirY * cos(rot_speed);
	old_plane_x = p->planeX;
	p->planeX = p->planeX * cos(rot_speed) - p->planeY * sin(rot_speed);
	p->planeY = old_plane_x * sin(rot_speed) + p->planeY * cos(rot_speed);
}

void	handle_rotation(t_game *game,double rot_speed)
{
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_LEFT))
		rotate_player(&game->player, -rot_speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_RIGHT))
		rotate_player(&game->player, rot_speed);
}

void	handle_movement(t_game *game, double dirX, double dirY)
{
	double	speed;

	speed = game->player.move_speed;
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_W))
		move_up(game, dirX, dirY, speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_S))
		move_down(game, dirX, dirY, speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_A))
		move_left(game, dirX, dirY, speed);
	if (mlx_is_key_down(game->res.mlx, MLX_KEY_D))
		move_right(game, dirX, dirY, speed);
}
