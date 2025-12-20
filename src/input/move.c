/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:29:08 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:28:43 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	move_up(t_game *g, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + dir_x * speed;
	new_y = g->player.pos_y + dir_y * speed;
	attempt_move(g, new_x, new_y);
}

void	move_down(t_game *g, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x - dir_x * speed;
	new_y = g->player.pos_y - dir_y * speed;
	attempt_move(g, new_x, new_y);
}

void	move_left(t_game *g, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + dir_y * speed;
	new_y = g->player.pos_y - dir_x * speed;
	attempt_move(g, new_x, new_y);
}

void	move_right(t_game *g, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x - dir_y * speed;
	new_y = g->player.pos_y + dir_x * speed;
	attempt_move(g, new_x, new_y);
}
