/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:53:04 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 23:02:14 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"


void	set_player_start_position(char identifier, t_map_data *map_data, size_t j)
{
	if (identifier == 'N')
		map_data->player_start_angle = 3 * M_PI / 2;
	else if (identifier == 'S')
		map_data->player_start_angle = M_PI / 2;
	else if (identifier == 'E')
		map_data->player_start_angle = 0.0;
	else if (identifier == 'W')
		map_data->player_start_angle = M_PI;

}

// Save a single line of the map into the map array.
// 'line' is the string representation of the map line.
int	save_the_map_line(char *line, int *map_row,t_map_data *map_data)
{
	size_t	j;

	j = 0;
	while (j < map_data->map_cols)
	{
		if (line[j] == '1')
			map_row[j] = 1;
		else if (line[j] == '0' || line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
		{
			map_row[j] = 0;
			if (line[j] != '0')
			{
				map_data->player_start_x = j;
				map_data->player_start_y = map_data->map_rows;
				set_player_start_position(line[j], map_data, j);
			}
		}
		else
			return (error_msg("Error: Invalid character in map line.\n"), -1);
		j++;
	}
	return (1);
}
