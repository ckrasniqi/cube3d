/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:29:08 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/17 19:06:37 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	move_up(t_game *g, double dirX, double dirY, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.posX + dirX * speed;
	new_y = g->player.posY + dirY * speed;
	attempt_move(g, new_x, new_y);
}

void	move_down(t_game *g, double dirX, double dirY, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.posX - dirX * speed;
	new_y = g->player.posY - dirY * speed;
	attempt_move(g, new_x, new_y);
}

void	move_left(t_game *g, double dirX, double dirY, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.posX + dirY * speed;
	new_y = g->player.posY - dirX * speed;
	attempt_move(g, new_x, new_y);
}

void	move_right(t_game *g, double dirX, double dirY, double speed)
{
	double	new_x;
	double	new_y;

	new_x = g->player.posX - dirY * speed;
	new_y = g->player.posY + dirX * speed;
	attempt_move(g, new_x, new_y);
}
