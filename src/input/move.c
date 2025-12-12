/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:29:08 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 19:27:18 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	move_up(t_game *g, double dirX, double dirY, double speed)
{
	double	newX;
	double	newY;

	newX = g->player.posX + dirX * speed;
	newY = g->player.posY + dirY * speed;
	attempt_move(g, newX, newY);
}

void	move_down(t_game *g, double dirX, double dirY, double speed)
{
	double	newX;
	double	newY;

	newX = g->player.posX - dirX * speed;
	newY = g->player.posY - dirY * speed;
	attempt_move(g, newX, newY);
}

void	move_left(t_game *g, double dirX, double dirY, double speed)
{
	double	newX;
	double	newY;

	newX = g->player.posX + dirY * speed;
	newY = g->player.posY - dirX * speed;
	attempt_move(g, newX, newY);
}

void	move_right(t_game *g, double dirX, double dirY, double speed)
{
	double	newX;
	double	newY;

	newX = g->player.posX - dirY * speed;
	newY = g->player.posY + dirX * speed;
	attempt_move(g, newX, newY);
}
