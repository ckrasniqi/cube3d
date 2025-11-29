/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:39:29 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/28 22:05:13 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	map_data_init(t_map_data *map_data)
{
	ft_memset(map_data, 0, sizeof(t_map_data));
	map_data->no_path = NULL;
	map_data->so_path = NULL;
	map_data->we_path = NULL;
	map_data->ea_path = NULL;
	map_data->parsed_textures = 0;
	map_data->floor_color = 0;
	map_data->ceiling_color = 0;
	map_data->parsed_colors = 0;
	map_data->file_contents = NULL;
	map_data->line_count = 0;
	map_data->map = NULL;
	map_data->map_copy = NULL;
	map_data->map_start_idx = 0;
	map_data->map_rows = 0;
	map_data->map_cols = 0;
	map_data->pixels = malloc(sizeof(uint32_t) * 720 * 720);
	if (!map_data->pixels)
	{
		error_msg("Failed to allocate memory for map pixels.\n");
		free_map_data(map_data);
	}
}

void	player_data_init(t_player *player)
{
	ft_memset(player, 0, sizeof(t_player));
	player->posX = -1.0;
	player->posY = -1.0;
	player->dirX = 0.0;
	player->dirY = 0.0;
	player->planeX = 0.0;
	player->planeY = 0.0;
	player->fov = 60.0;
	player->move_speed = 0.1;
	player->rot_speed = 5.0;
}

int	find_next_nonblank(char **lines, int start, int line_count)
{
	int	j;

	j = start;
	while (j < line_count)
	{
		if (lines[j] && lines[j][0] != '\n')
			return (j);
		j++;
	}
	return (j);
}

int	missing_color_texture(t_map_data *map_data)
{
	if (map_data->parsed_colors < 2 || map_data->parsed_textures < 4
		|| !map_data->no_path || !map_data->so_path || !map_data->we_path
		|| !map_data->ea_path)
		return (-1);
	return (0);
}

// void	print_everything_map_data(t_map_data *map_data, char **lines, \
// 	int line_count)
// {
// 	printf("NO Path: %s\n", map_data->no_path);
// 	printf("SO Path: %s\n", map_data->so_path);
// 	printf("WE Path: %s\n", map_data->we_path);
// 	printf("EA Path: %s\n", map_data->ea_path);
// 	printf("Floor Color: 0x%06X\n", map_data->floor_color);
// 	printf("Ceiling Color: 0x%06X\n", map_data->ceiling_color);
// 	printf("Map Start Index: %d\n", map_data->map_start_idx);
// 	printf("Map Rows: %d\n", map_data->map_rows);
// 	printf("Map Columns: %d\n", map_data->map_cols);
// 	printf("Player Start Position: (%d, %d)\n",
// 		map_data->player_start_x, map_data->player_start_y);
// 	printf("Player Start Angle: %.2f radians\n", map_data->player_start_angle);
// 	// printf("Map Data:\n");
// 	(void)line_count;
// 	(void)lines;
// 	for (int i = 0; i < map_data->map_rows; i++)
// 	{
// 		printf("%s", map_data->file_contents[i]);
// 		printf("\n");
// 	}


// }
