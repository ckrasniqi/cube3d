/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:39:29 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 14:40:51 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	map_data_init(t_map_data *map_data)
{
	map_data->no_path = NULL;
	map_data->so_path = NULL;
	map_data->we_path = NULL;
	map_data->ea_path = NULL;
	map_data->parsed_textures = 0;
	map_data->floor_color = 0;
	map_data->ceiling_color = 0;
	map_data->parsed_colors = 0;
	map_data->map = NULL;
	map_data->map_start_idx = 0;
	map_data->map_rows = 0;
	map_data->map_cols = 0;
	map_data->player_start_x = -1;
	map_data->player_start_y = -1;
	map_data->player_start_angle = 0.0;
}

void	print_everything_map_data(t_map_data *map_data)
{
	printf("NO Path: %s\n", map_data->no_path);
	printf("SO Path: %s\n", map_data->so_path);
	printf("WE Path: %s\n", map_data->we_path);
	printf("EA Path: %s\n", map_data->ea_path);
	printf("Floor Color: 0x%06X\n", map_data->floor_color);
	printf("Ceiling Color: 0x%06X\n", map_data->ceiling_color);
	printf("Map Start Index: %d\n", map_data->map_start_idx);
	printf("Map Rows: %zu\n", map_data->map_rows);
	printf("Map Columns: %zu\n", map_data->map_cols);
}
