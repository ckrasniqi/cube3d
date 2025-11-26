/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:42:43 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/26 18:13:24 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	ft_flood_fill(char **map, int x, int y, t_map_data *m)
{
	if (x < 0 || y < 0 || x >= m->map_cols || y >= m->map_rows)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	else
	{
		map[y][x] = 'X';
		ft_flood_fill(map, x + 1, y, m);
		ft_flood_fill(map, x - 1, y, m);
		ft_flood_fill(map, x, y + 1, m);
		ft_flood_fill(map, x, y - 1, m);
	}
}

void	fill_map(t_map_data *m, int x, int y)
{
	ft_flood_fill(m->map_copy, x, y, m);
}

int	is_there_open_path(t_map_data *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map_rows)
	{
		j = 0;
		while (j < m->map_cols)
		{
			if (m->map_copy[i][j] != '1' && m->map_copy[i][j] != 'X')
				return (error_msg("Open path found in map.\n"), -1);
			j++;
		}
		i++;
	}
	return (1);
}

// void	print_map_only(char **map, int rows, int cols, int start_idx)
// {
// 	int	i;
// 	int	j;

// 	printf("Map at start index %d:\n", start_idx);
// 	for (i = 0; i < rows; i++)
// 	{
// 		for (j = 0; j < cols; j++)
// 		{
// 			if (map[i][j] == '\0')
// 				break ;
// 			printf("%c", map[i][j]);
// 		}
// 		printf("\n");
// 	}
// }

int	copy_map(t_map_data *map_data, int start_idx)
{
	int	i;

	map_data->map = malloc(sizeof(char *) * (map_data->map_rows + 1));
	map_data->map_copy = malloc(sizeof(char *) * (map_data->map_rows + 1));
	if (!map_data->map || !map_data->map_copy)
		return (error_msg("Memory allocation failed for map copy.\n"), -1);
	i = 0;
	while (i < map_data->map_rows)
	{
		map_data->map[i] = ft_strdup(map_data->file_contents[start_idx + i]);
		map_data->map_copy[i] = ft_strdup(map_data->file_contents[start_idx
				+ i]);
		if (!map_data->map[i] || !map_data->map_copy[i])
			return (error_msg("Memory allocation failed for map rows.\n"), -1);
		i++;
	}
	map_data->map[i] = NULL;
	map_data->map_copy[i] = NULL;
	return (1);
}

int	check_enclosed(t_map_data *m)
{
	fill_map(m, m->player_start_y, m->player_start_x);
	if (is_there_open_path(m) == -1)
		return (-1);
	return (0);
}
