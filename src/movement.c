/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 22:21:01 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/29 20:30:20 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	if (!player)
		return ;
	old_dir_x = player->dirX;
	player->dirX = player->dirX * cos(angle) - player->dirY * sin(angle);
	player->dirY = old_dir_x	* sin(angle) + player->dirY * cos(angle);
	old_plane_x = player->planeX;
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = old_plane_x	* sin(angle) + player->planeY * cos(angle);
}

void	handle_movement(t_game *g, double dirX, double dirY)
{
	double	move_step;

	move_step = g->player.move_speed * g->time.delta_time;
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_W))
		move_up(g, dirX, dirY, move_step);
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_S))
		move_down(g, dirX, dirY, move_step);
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_A))
		move_left(g, dirX, dirY, move_step);
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_D))
		move_right(g, dirX, dirY, move_step);
}

void	handle_rotation(t_game *g, double rot_angle, double rot_speed, double dt)
{
	rot_angle = rot_speed * g->cfg.tile_size * dt;
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_LEFT))
	{
		rotate_player(&g->player, -rot_angle);
		render_mini_map(g, &g->map_data);
	}
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_RIGHT))
	{
		rotate_player(&g->player, rot_angle);
		render_mini_map(g, &g->map_data);
	}
}
