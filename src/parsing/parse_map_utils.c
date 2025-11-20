/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:53:04 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/20 19:26:18 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	set_player_start_position(char identifier, t_map_data *map_data, int x)
{
	map_data->player_start_x = x;
	if (identifier == 'N' || identifier == 'S')
		map_data->player_start_y = map_data->map_rows;
	else if (identifier == 'E' || identifier == 'W')
		map_data->player_start_y = map_data->map_rows;
	if (identifier == 'N')
		map_data->player_start_angle = 3 * M_PI / 2;
	else if (identifier == 'S')
		map_data->player_start_angle = M_PI / 2;
	else if (identifier == 'E')
		map_data->player_start_angle = 0.0;
	else if (identifier == 'W')
		map_data->player_start_angle = M_PI;
}

int	not_part_of_map(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n' || c == '\r' || c == '\0')
		return (0);
	return (1);
}

int	check_for_invalid_characters(char **lines, t_map_data *map_data)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < map_data->map_rows)
	{
		j = -1;
		while (++j < map_data->map_cols)
		{
			c = lines[map_data->map_start_idx + i][j];
			if (not_part_of_map(c))
				return (error_msg("Invalid character in map.\n"), -1);
			else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (map_data->player_start_x != -1
					&& map_data->player_start_y != -1)
					return (error_msg("Multiple player start positions.\n"),
						-1);
				set_player_start_position(c, map_data, j);
			}
		}
	}
	return (1);
}

// Save a single line of the map into the map array.
// 'line' is the string representation of the map line.
int	save_the_map_line(char *line, int *map_row, t_map_data *map_data)
{
	int	j;
	int	len;
	char	c;

	j = 0;
	len = ft_strlen(line);
	while (j < map_data->map_cols)
	{
		/* get character at j,
			or treat missing chars as space for padding */
		if (j < len)
			c = line[j];
		else
			c = ' ';
		if (c == '1')
			map_row[j] = 1;
		else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			map_row[j] = 0;
			if (c != '0')
			{
				map_data->player_start_x = j;
				map_data->player_start_y = map_data->map_rows;
				set_player_start_position(c, map_data, j);
			}
		}
		else if (c == ' ' || c == '\n' || c == '\r' || c == '\0')
		{
			/* treat missing/padding chars as empty space */
			map_row[j] = 0;
		}
		else
			return (error_msg("Invalid character in map line.\n"), -1);
		j++;
	}
	return (1);
}
