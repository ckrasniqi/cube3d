/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:41:27 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 16:34:56 by ckrasniq         ###   ########.fr       */
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
		return (error_msg("Error: Filename\n"), 0);
	if (ft_strlen(filename) < 4)
		return (error_msg("Error: Filename\n"), 0);
	if (!name_check(filename))
		return (error_msg("Error: Invalid file extension. Expected .cub\n"), 0);
	return (1);
}

char	**get_all_lines(int fd, int *line_count)
{
	char	**lines;
	char	*line;
	int		i;
	int		temp;

	temp = 10;
	lines = malloc(sizeof(char *) * (temp + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		lines[i++] = line;
		if (i >= temp - 1)
		{
			temp *= 2;
			lines = realloc(lines, sizeof(char *) * (temp + 1));
			if (!lines)
				return (NULL);
		}
		(*line_count)++;
	}
	lines[i] = NULL;
	return (lines);
}

int	parse_cub_file(const char *filename, t_map_data *map_data)
{
	int		fd;
	int		line_count;
	char	**lines;
	int		ret;

	line_count = 0;
	if (!validate_filename(filename))
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Error: Failed to open map file.\n"), -1);
	lines = get_all_lines(fd, &line_count);
	if (!lines)
		return (close(fd), error_msg("Error: Failed to read file lines.\n"), -1);
	ft_memset(map_data, 0, sizeof(t_map_data));
	map_data_init(map_data);
	ret = parse_map_data(map_data, lines, line_count);
	if (ret == 0 || ret == -1)
		return (close(fd), free_lines(lines, line_count),
			free_map_data(map_data), -1);
	free_lines(lines, line_count);
	// print_everything_map_data(map_data);
	return (close(fd), 1);
}
