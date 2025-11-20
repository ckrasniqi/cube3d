/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:41:27 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/16 19:13:20 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	name_check(const char *filename)
{
	const char	*ext = ft_strrchr(filename, '.');

	if (!ext || ft_strcmp(ext, ".cub") != 0)
		return (0);
	return (1);
}

int	validate_filename(const char *filename)
{
	if (!filename)
		return (error_msg("Filename\n"), 0);
	if (ft_strlen(filename) < 4)
		return (error_msg("Filename\n"), 0);
	if (!name_check(filename))
		return (error_msg("Invalid file extension. Expected .cub\n"), 0);
	return (1);
}

char	**get_all_lines(int fd, t_map_data *map_data, char **first_line)
{
	char	**lines;
	char	*line;
	int		line_count;
	int		capacity;

	capacity = 10;
	line_count = 0;
	lines = malloc(sizeof(char *) * capacity);
	if (!lines)
		return (NULL);
	lines[line_count++] = *first_line;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line_count >= capacity)
			lines = realloc(lines, sizeof(char *) * capacity * 2);
		if (!lines)
			return (NULL);
		lines[line_count++] = line;
	}
	map_data->line_count = line_count;
	return (lines);
}

int	parse_cub_file(const char *filename, t_map_data *map_data)
{
	int		fd;
	char	*line;

	if (!validate_filename(filename))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Failed to open map file.\n"), -1);
	line = get_next_line(fd);
	if (!line)
		return (error_msg("failed to read file lines.\n"), -1);
	map_data->file_contents = get_all_lines(fd, map_data, &line);
	if (!map_data->file_contents)
		return (error_msg("Failed to read file lines.\n"), -1);
	map_data_init(map_data);
	if (parse_map_data(map_data, map_data->file_contents,
			map_data->line_count) == -1)
		return (free_lines(map_data->file_contents, map_data->line_count), -1);
	print_everything_map_data(map_data, map_data->file_contents,
		map_data->line_count);
	return (1);
}
