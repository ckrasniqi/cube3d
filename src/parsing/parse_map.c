/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:39:44 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 23:01:07 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

size_t	count_rows(char **lines, int start_idx, int line_count)
{
	size_t	rows;
	size_t	i;

	rows = 0;
	i = 0;
	while ((size_t)(start_idx + i) < (size_t)line_count)
	{
		if (lines[start_idx + i] && lines[start_idx + i][0] != '\n')
			rows++;
		i++;
	}
	return (rows);
}

size_t	count_width(char **lines, int start_idx, size_t rows)
{
	size_t	max_width;
	size_t	current_width;
	size_t	i;

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

int	validate_map_lines(char **lines, t_map_data *map_data)
{
	size_t	i;

	i = 0;
	while (i < map_data->map_rows)
	{
		char	*line = lines[map_data->map_start_idx + i];
		size_t	j;

		j = 0;
		while (j < ft_strlen(line))
		{
			if (line[j] != '0' && line[j] != '1' && line[j] != '2'
				&& line[j] != 'N' && line[j] != 'S' && line[j] != 'E'
				&& line[j] != 'W' && line[j] != ' ')
			{
				return (error_msg("Error: Invalid character in map.\n"), -1);
			}
			j++;
		}
		i++;
	}
	// flood_fill_map_borders(lines, map_data);
	return (1);
}

int	parse_map_line(char **lines, t_map_data *map_data, int line_count)
{
	size_t	i;

	i = 0;
	map_data->map_rows = count_rows(lines, map_data->map_start_idx, line_count);
	map_data->map_cols = count_width(lines, map_data->map_start_idx,
			map_data->map_rows);
	if (validate_map_lines(lines, map_data) != 1)
		return (-1);
	map_data->map = malloc(sizeof(int *) * map_data->map_cols);
	if (!map_data->map)
		return (error_msg("Error: Memory allocation failed.\n"), -1);
	while (i < map_data->map_rows)
	{
		map_data->map[i] = malloc(sizeof(int) * map_data->map_cols);
		if (!map_data->map[i])
			return (error_msg("Error: Memory allocation failed.\n"), -1);
		save_the_map_line(lines[map_data->map_start_idx + i],
			map_data->map[i], map_data);
		i++;
	}
	return (1);
}

int	parse_map_data(t_map_data *map_data, char **lines, int line_count)
{
	int		i;
	char	*line;
	char	*trim;
	int		ret;

	i = 0;
	while (i < line_count)
	{
		line = lines[i];
		if (!line)
		{
			i++;
			continue ;
		}
		trim = ft_skip_whitespace(line);
		ret = parse_line(trim, map_data);
		if (ret == -1)
			return (-1);
		if (ret != -1)
		{
			if (map_data->parsed_textures == 4 && map_data->parsed_colors == 2)
			{
				map_data->map_start_idx = find_next_nonblank(lines, i + 1,
						line_count);
				return (parse_map_line(lines, map_data, line_count));
			}
		}
		i++;
	}
	return (0);
}
