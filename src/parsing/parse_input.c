/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:34:49 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 19:35:14 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	name_check(const char *filename)
{
	const char	*ext = ft_strrchr(filename, '.');

	if (!ext || ft_strcmp(ext, ".cub") != 0)
		ft_error("Error: Invalid file extension. Expected .cub\n");
}

void	validate_sides(const char *filename, t_map_data **map_data)
{
	(void)filename;
	(void)map_data;
}

void	validate_floor_ceiling(const char *filename, t_map_data **map_data)
{
	(void)filename;
	(void)map_data;
}

void	validate_map_structure(const char *filename, t_map_data **map_data)
{
	(void)filename;
	(void)map_data;
}


int	floor_ceiling_parser(const char *line, t_map_data *map_data)
{
	if (!(map_data->floor_color) && ft_strncmp(line, "F ", 2) == 0)
	{
		printf("%s\n", line);
		return (1);
	}
	else if (!(map_data->ceiling_color) && ft_strncmp(line, "C ", 2) == 0)
	{
		printf("%s\n", line);
		return (1);

	}
	return (0);
}
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}

char *ft_skip_whitespace(const char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (char *)str;
}

int	parse_texture_path(const char *line, const char *prefix, char *path)
{
	char	*start;
	char	*end;

	line = ft_skip_whitespace(line);
	if (ft_strncmp(line, prefix, 2) != 0)
		return (0);
	line += 2;
	line = ft_skip_whitespace(line);
	if (*line == '\0' || *line == '\n')
		ft_error("Error: Texture path missing after prefix.\n");
	start = (char *)line;
	while (*line != '\0' && *line != '\n' && !ft_isspace(*line))
		line++;
	end = (char *)line;
	*end = '\0';
	path = malloc(end - start + 1);
	if (!path)
	{
		ft_error("Error: Memory allocation failed for texture path.\n");
		return (0);
	}
	ft_strlcpy(path, start, end - start + 1);
	path[end - start] = '\0';
	printf("Parsed %s texture path: %s\n", prefix, path);
	return (1);
}

int		parse_line(const char *line, t_map_data *map_data)
{
	if (line == NULL || map_data == NULL)
		return (1);
	if (parse_texture_path(line, "NO", map_data->no_path) == 1)
		return (1);
	if (parse_texture_path(line, "SO", map_data->so_path) == 1)
		return (1);
	if (parse_texture_path(line, "WE", map_data->we_path) == 1)
		return (1);
	if (parse_texture_path(line, "EA", map_data->ea_path) == 1)
		return (1);
	if (floor_ceiling_parser(line, map_data) == 1)
		return (1);
	return (0);
}

int	save_map_data(const char *filename, t_map_data *map_data)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Error: Unable to open file.\n");
	while ((line = get_next_line(fd)) != NULL)
	{
		parse_line(line, map_data);
	}
	if (line)
		free(line);
	close(fd);
	return 0;
}

void	parse_map(const char *filename, t_map_data *map_data)
{
	ft_memset(map_data, 0, sizeof(t_map_data));
	if (ft_strlen(filename) < 4)
	{
		fprintf(stderr, "Error: Filename too short to be valid.\n");
		exit(EXIT_FAILURE);
	}
	name_check(filename);
	if (save_map_data(filename, map_data) == 1)
		// Error already handled in save_map_data
		return ;
	validate_sides(filename, &map_data);
	validate_floor_ceiling(filename, &map_data);
	// printf("Parsing map from file: %s\n", filename);
}
