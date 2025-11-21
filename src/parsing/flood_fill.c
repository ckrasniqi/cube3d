/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:42:43 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/21 14:16:12 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	flood(t_map_data *m, int y, int x, int **visited)
{
	char	c;

	// check out-of-bounds → leak
	if (x < 0 || y < 0 || x >= m->map_cols || y >= m->map_rows)
		return (1);
	c = m->map_copy[y][x];
	// a space = VOID = leak
	if (c == ' ')
		return (1);
	if (c == '1') // walls block
		return (0);
	if (visited[y][x])
		return (0);
	visited[y][x] = 1;
	// flood in all 4 directions (if any return leak → leak)
	if (flood(m, y + 1, x, visited))
		return (1);
	if (flood(m, y - 1, x, visited))
		return (1);
	if (flood(m, y, x + 1, visited))
		return (1);
	if (flood(m, y, x - 1, visited))
		return (1);
	return (0);
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
	int	**visited;
	int	i;

	// allocate visited matrix
	visited = malloc(sizeof(int *) * m->map_rows);
	if (!visited)
		return (error_msg("Malloc failed\n"), -1);
	for (i = 0; i < m->map_rows; i++)
	{
		visited[i] = ft_calloc(m->map_cols, sizeof(int));
		if (!visited[i])
			return (error_msg("Malloc failed\n"), -1);
	}
	// run flood fill from player start
	if (flood(m, m->player_start_y, m->player_start_x, visited))
	{
		error_msg("Map is not enclosed\n");
		return (-1);
	}
	return (0);
}
