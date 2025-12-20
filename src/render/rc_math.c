/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:18:10 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:28:02 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	preform_dda(t_game *game, t_raycaster *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (game->map_data.map[rc->map_y][rc->map_x] == '1')
			rc->hit = 1;
	}
}

double	find_delta_dist(double rayDir)
{
	if (rayDir == 0)
		return (1e30);
	return (fabs(1.0 / rayDir));
}

void	calculate_step_and_side_dist(t_raycaster *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->pos_y) * rc->delta_dist_y;
	}
}

void	calculate_wall_projection(t_game *game, t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->side_dist_x - rc->delta_dist_x);
	else
		rc->perp_wall_dist = (rc->side_dist_y - rc->delta_dist_y);
	if (rc->perp_wall_dist < 0.0001)
		rc->perp_wall_dist = 0.0001;
	rc->line_height = (int)(game->cfg.height / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + game->cfg.height / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + game->cfg.height / 2;
	if (rc->draw_end >= game->cfg.height)
		rc->draw_end = game->cfg.height - 1;
	if (rc->side == 0)
		rc->wall_x = rc->pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wall_x = rc->pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wall_x -= floor(rc->wall_x);
}

void	init_raycaster_variables(t_game *game, t_raycaster *rc)
{
	rc->pos_x = game->player.pos_x;
	rc->pos_y = game->player.pos_y;
	rc->map_x = (int)rc->pos_x;
	rc->map_y = (int)rc->pos_y;
	rc->hit = 0;
	rc->side = 0;
	rc->perp_wall_dist = 0.0;
	rc->delta_dist_x = find_delta_dist(rc->ray_dir_x);
	rc->delta_dist_y = find_delta_dist(rc->ray_dir_y);
	calculate_step_and_side_dist(rc);
}
