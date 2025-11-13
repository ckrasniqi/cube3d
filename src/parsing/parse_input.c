/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:34:49 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 22:02:00 by ckrasniq         ###   ########.fr       */
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
int	color_check(char *line, int *r, int *g, int *b)
{
	if (*line == '\0' || *line == '\n')
		return ((error_msg("Error: Color values missing after prefix.\n"), 1));
	*r = ft_atoi(line);
	while (*line != '\0' && *line != '\n' && *line != ',')
		line++;
	if (*line != ',')
		return ((error_msg("Error: Invalid color format. Expected R,G,B.\n"),
				1));
	line++;
	*g = ft_atoi(line);
	while (*line != '\0' && *line != '\n' && *line != ',')
		line++;
	if (*line != ',')
		return ((error_msg("Error: Invalid color format. Expected R,G,B.\n"),
				1));
	line++;
	*b = ft_atoi(line);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (error_msg("Color values must be between 0 and 255"), 1);
	return (0);
}

int	parse_color(char *line, const char *prefix, t_map_data *map_data, uint32_t *color)
{
	int	r;
	int	g;
	int	b;

	line = ft_skip_whitespace(line);
	if (ft_strncmp(line, prefix, ft_strlen(prefix)) != 0)
		return (0);
	line += ft_strlen(prefix);
	line = ft_skip_whitespace(line);
	if (color_check(line, &r, &g, &b) == 1)
		return (1);
	*color = (r << 16) | (g << 8) | b;
	map_data->parsed_colors++;
	return (1);
}

int	parse_texture_path(char *line, const char *prefix, t_map_data *map_data, char *path)
{
	char	*start;
	char	*end;

	line = ft_skip_whitespace(line);
	if (ft_strncmp(line, prefix, 2) != 0)
		return (0);
	line += 2;
	line = ft_skip_whitespace(line);
	if (*line == '\0' || *line == '\n')
		return (error_msg("Error: Texture path missing after prefix.\n"), 1);
	start = line;
	while (*line != '\0' && *line != '\n' && !ft_isspace(*line))
		line++;
	end = line;
	*end = '\0';
	path = malloc(end - start + 1);
	if (!path)
		return (error_msg("Error: Memory allocation failed for texture path.\n"), 1);
	ft_strlcpy(path, start, end - start + 1);
	path[end - start] = '\0';
	map_data->parsed_textures++;
	return (0);
}

size_t count_rows(char **lines, int start_idx, int line_count)
{
	size_t	rows;
	int		i;

	rows = 0;
	i = start_idx;
	while (i < line_count)
	{
		if (lines[i] == NULL || *lines[i] == '\0' || *lines[i] == '\n')
			break ;
		rows++;
		i++;
	}
	return (rows);
}

int parse_map_line(char **lines, t_map_data *map_data, int line_count)
{
	map_data->map_rows = count_rows(lines, map_data->map_start_idx, line_count);
}

int	parse_line(char **lines, t_map_data *map_data, int i, int line_count)
{
	while (i < line_count)
	{
		char *line = lines[i];

		if (line == NULL || map_data == NULL)
			return (1);
		if (ft_strncmp(line, "NO ", 3) == 0)
			return (parse_texture_path(line, "NO", map_data, map_data->no_path));
		else if (ft_strncmp(line, "SO ", 3) == 0)
			return (parse_texture_path(line, "SO", map_data, map_data->so_path));
		else if (ft_strncmp(line, "WE ", 3) == 0)
			return (parse_texture_path(line, "WE", map_data, map_data->we_path));
		else if (ft_strncmp(line, "EA ", 3) == 0)
			return (parse_texture_path(line, "EA", map_data, map_data->ea_path));
		else if (ft_strncmp(line, "F ", 2) == 0)
			return (parse_color(line, "F", map_data, &map_data->floor_color));
		else if (ft_strncmp(line, "C ", 2) == 0)
			return (parse_color(line, "C", map_data, &map_data->ceiling_color));
		else if (ft_isdigit(*line) || *line == ' ')
			return (parse_map_line(lines, map_data, line_count), map_data->map_start_idx = i);
		else
			i++;
	}
	return (0);
}

char **get_all_lines(int fd, int line_count)
{
	char	**lines;
	char	*line;
	int		i;

	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		lines[i] = line;
		i++;
	}
	lines[i] = NULL;
	return (lines);
}

int count_lines(int fd)
{
	char	*line;
	int		line_count;

	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	return (line_count);
}

int	save_map_data(const char *filename, t_map_data *map_data)
{
	int		fd1;
	int		fd2;
	char	**lines;
	int		line_count;
	int 	i;

	fd1 = open(filename, O_RDONLY);
	fd2 = open(filename, O_RDONLY);
	line_count = count_lines(fd1);
	lines = get_all_lines(fd2, line_count);
	i = 0;
	while (i < line_count)
	{
		if (parse_line(lines, map_data, i, line_count) == 1)
		{
			free_lines(lines, line_count);
			free_map_data(map_data);
			return (1);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
}

void	map_data_init(t_map_data *map_data)
{
	map_data->no_path = NULL;
	map_data->so_path = NULL;
	map_data->we_path = NULL;
	map_data->ea_path = NULL;
	map_data->parsed_textures = 0;
	map_data->floor_color = 0;
	map_data->ceiling_color = 0;
	map_data->parsed_colors = 0;
	map_data->map = NULL;
	map_data->map_start_idx = 0;
	map_data->map_rows = 0;
	map_data->map_cols = 0;
	map_data->player_start_x = -1;
	map_data->player_start_y = -1;
	map_data->player_start_angle = 0.0;
	return ;
}

void	parse_cub_file(const char *filename, t_map_data *map_data)
{
	ft_memset(map_data, 0, sizeof(t_map_data));
	map_data_init(map_data);
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
