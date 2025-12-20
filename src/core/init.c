/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:29:54 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:26:44 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	time_data_init(t_time *time)
{
	if (ft_memset(time, 0, sizeof(t_time)) == NULL)
		return (-1);
	time->delta_time = 0.0;
	time->now = 0.0;
	time->last = 0.0;
	time->acc = 0.0;
	time->fixed_dt = 0.016;
	return (0);
}

int	settings_data_init(t_settings *settings)
{
	if (ft_memset(settings, 0, sizeof(t_settings)) == NULL)
		return (-1);
	settings->tile_size = 64;
	settings->width = WIDTH;
	settings->height = HEIGHT;
	return (0);
}

int	raycaster_data_init(t_raycaster *raycast)
{
	if (ft_memset(raycast, 0, sizeof(t_raycaster)) == NULL)
		return (-1);
	raycast->map_x = 0;
	raycast->map_y = 0;
	raycast->camera_x = 0.0;
	raycast->ray_dir_x = 0.0;
	raycast->ray_dir_y = 0.0;
	raycast->delta_dist_x = 0.0;
	raycast->delta_dist_y = 0.0;
	raycast->side_dist_x = 0.0;
	raycast->side_dist_y = 0.0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->pos_x = 0.0;
	raycast->pos_y = 0.0;
	raycast->hit = 0;
	raycast->side = 0;
	return (0);
}

int	resources_init(t_resources *res)
{
	if (ft_memset(res, 0, sizeof(t_resources)) == NULL)
		return (-1);
	res->mlx = NULL;
	res->image = NULL;
	return (0);
}

int	struct_init(t_game *game)
{
	if (ft_memset(game, 0, sizeof(t_game)) == NULL)
		return (-1);
	if (player_data_init(&game->player) == -1)
		return (-1);
	if (time_data_init(&game->time) == -1)
		return (-1);
	if (settings_data_init(&game->cfg) == -1)
		return (-1);
	if (raycaster_data_init(&game->raycast) == -1)
		return (-1);
	if (resources_init(&game->res) == -1)
		return (-1);
	return (0);
}
