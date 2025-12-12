/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:42:43 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 19:27:34 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	ft_is_map_closed(char **map, int x, int y, t_map_data *m)
{
	if (x < 0 || y < 0 || x >= m->map_cols || y >= m->map_rows)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'E')
		return (1);

	map[y][x] = 'E';

	if (!ft_is_map_closed(map, x + 1, y, m))
		return (0);
	if (!ft_is_map_closed(map, x - 1, y, m))
		return (0);
	if (!ft_is_map_closed(map, x, y + 1, m))
		return (0);
	if (!ft_is_map_closed(map, x, y - 1, m))
		return (0);

	return (1);
}

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
