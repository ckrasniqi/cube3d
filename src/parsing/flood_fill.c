/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:42:43 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/20 19:35:00 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	flood_fill(char **map, int x, int y, t_map_data *map_data)
{
	if (x < 0 || y < 0 || x >= map_data->map_cols
		|| y >= map_data->map_rows)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'N' || map[y][x] == 'E'
		|| map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'X')
		return ;
	{
		map[y][x] = 'X';
		flood_fill(map, x + 1, y, map_data);
		flood_fill(map, x - 1, y, map_data);
		flood_fill(map, x, y + 1, map_data);
		flood_fill(map, x, y - 1, map_data);
	}
}

// void	print_map_only(char **map, int rows, int cols)
// {
// 	int	i;
// 	int	j;
// 	char *line = NULL;

// 	printf("Map Copy after copying:\n");
// 	for (i = 0; i < rows; i++)
// 	{
// 			line[i] = map[i];
// 			if (line[i] == '\n' || line[i] == '\0')
// 				break ;
// 			printf("%s", line[i]);
// 	}
// }

int	copy_map(t_map_data *map_data, int start_idx)
{
	int		i;

	map_data->map = malloc(sizeof(char *) * (map_data->map_rows + 1));
	map_data->map_copy = malloc(sizeof(char *) * (map_data->map_rows + 1));
	if (!map_data->map || !map_data->map_copy)
		return (error_msg("Memory allocation failed for map copy.\n"), -1);
	i = 0;
	while (i < map_data->map_rows)
	{
		map_data->map[i] = ft_strdup(map_data->file_contents[start_idx + i]);
		map_data->map_copy[i] = ft_strdup(map_data->file_contents[start_idx + i]);
		if (!map_data->map[i] || !map_data->map_copy[i])
			return (error_msg("Memory allocation failed for map rows.\n"), -1);
		i++;
	}
	map_data->map[i] = NULL;
	map_data->map_copy[i] = NULL;
	// print_map_only(map_data->map, map_data->map_rows, map_data->map_cols);
	return (1);
}

int	fill_map(char **lines, t_map_data *map_data)
{
	(void)lines;
	flood_fill(map_data->map_copy, map_data->player_start_x,
		map_data->player_start_y, map_data);
	while (1)
	{
		// Implement flood fill algorithm here
		break ;
	}
	return (1);
}
