/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:29:54 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/29 20:12:22 by ckrasniq         ###   ########.fr       */
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
	time->fixed_dt = 0.016; // Approx 60 FPS
	return (0);
}

int	settings_data_init(t_settings *settings)
{
	if (ft_memset(settings, 0, sizeof(t_settings)) == NULL)
		return (-1);
	settings->tile_size = 64;
	settings->width = 720;
	settings->height = 720;
	return (0);
}

int	input_data_init(t_input *input)
{
	if (ft_memset(input, 0, sizeof(t_input)) == NULL)
		return (-1);
	input->w_key = false;
	input->a_key = false;
	input->s_key = false;
	input->d_key = false;
	input->left_key = false;
	input->right_key = false;
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
	player_data_init(&game->player);
	input_data_init(&game->input);
	resources_init(&game->res);
	if (ft_memset(&game->time, 0, sizeof(t_time)) == NULL)
		return (-1);
	if (ft_memset(&game->cfg, 0, sizeof(t_settings)) == NULL)
		return (-1);
	if (ft_memset(&game->map_data, 0, sizeof(t_map_data)) == NULL)
		return (-1);
	return (0);
}

