/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:41:27 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 19:27:22 by ckrasniq         ###   ########.fr       */
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

char	**get_all_lines(const char *filename, t_map_data *map_data)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Opening file\n"), NULL);
	tmp = ft_strdup("");
	line = get_next_line(fd);
	if (!line)
		return (error_msg("Empty file\n"), NULL);
	while (line != NULL)
	{
		tmp = ft_strjoin(tmp, line);
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(tmp, '\n');
	while (map[map_data->line_count])
		map_data->line_count++;
	free(tmp);
	return (map);
}

int	parse_cub_file(const char *filename, t_map_data *map_data, t_game *game, t_player *p)
{
	if (!validate_filename(filename))
		return (-1);
	map_data_init(map_data);
	player_data_init(p);
	map_data->file_contents = get_all_lines(filename, map_data);
	if (!map_data->file_contents)
		return (-1);
	if (parse_map_data(map_data, map_data->file_contents,
			map_data->line_count, game) == -1)
		return (-1);
	return (1);
}
