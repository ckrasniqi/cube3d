/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:39:44 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/26 17:38:45 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	count_rows(char **lines, int start_idx, int line_count)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	while ((start_idx + i) < line_count)
	{
		if (lines[start_idx + i] && lines[start_idx + i][0] != '\n')
			rows++;
		i++;
	}
	return (rows);
}

int	count_width(char **lines, int start_idx, int rows)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (i < rows)
	{
		current_width = ft_strlen(lines[start_idx + i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	validate_and_save(t_map_data *map_data)
{
	if (copy_map(map_data, map_data->map_start_idx) != 1)
		return (-1);
	if (map_data->map[0] == NULL)
		return (error_msg("No map"), -1);
	if (check_for_invalid_characters(map_data->map, map_data) != 1)
		return (-1);
	if (map_data->player_start_x == -1)
		return (error_msg("No player start position found in map.\n"), -1);
	if (pad_map_copy(map_data) == -1)
		return (-1);
	if (check_enclosed(map_data) == -1)
		return (-1);

	// if (fill_map(map_data->file_contents, map_data) != 1)
	// 	return (-1);
	return (1);
}

int	parse_map_line(char **lines, t_map_data *map_data, int line_count)
{
	map_data->map_rows = count_rows(lines, map_data->map_start_idx, line_count);
	map_data->map_cols = count_width(lines, map_data->map_start_idx,
			map_data->map_rows);
	if (validate_and_save(map_data) != 1)
		return (-1);
	return (1);
}

int	parse_map_data(t_map_data *map_data, char **lines, int line_count)
{
	int		i;
	char	*line;
	char	*trim;

	i = -1;
	while (i++ < line_count)
	{
		line = lines[i];
		trim = ft_skip_whitespace(line);
		if (parse_line(trim, map_data) == -1)
			return (-1);
		if (reached_maximums(map_data) == -1)
			return (-1);
		if (reached_maximums(map_data) == 1)
		{
			map_data->map_start_idx = find_next_nonblank(lines, i + 1,
					line_count);
			return (parse_map_line(lines, map_data, line_count));
		}
	}
	if (missing_color_texture(map_data) == -1)
		return (error_msg("Incomplete map data.\n"), -1);
	return (0);
}
