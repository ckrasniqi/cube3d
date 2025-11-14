/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:34:49 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 14:37:03 by ckrasniq         ###   ########.fr       */
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

void	debug_print_lines(char **lines, int line_count)
{
	for (int i = 0; i < line_count; i++)
		printf("Line %d: %s", i + 1, lines[i]);
}

int	color_check(char *line, int *r, int *g, int *b)
{
	if (*line == '\0' || *line == '\n')
		return ((error_msg("Error: Color values missing after prefix.\n"), -1));
	*r = ft_atoi(line);
	while (*line != '\0' && *line != '\n' && *line != ',')
		line++;
	if (*line != ',')
		return ((error_msg("Error: Invalid color format. Expected R,G,B.\n"),
				-1));
	line++;
	*g = ft_atoi(line);
	while (*line != '\0' && *line != '\n' && *line != ',')
		line++;
	if (*line != ',')
		return ((error_msg("Error: Invalid color format. Expected R,G,B.\n"),
				-1));
	line++;
	*b = ft_atoi(line);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (error_msg("Color values must be between 0 and 255"), -1);
	return (1);
}

int	parse_color(char *line, const char *prefix, t_map_data *map_data,
		uint32_t *color)
{
	int		r;
	int		g;
	int		b;
	size_t	prefix_len;

	line = ft_skip_whitespace(line);
	prefix_len = ft_strlen(prefix);
	if (ft_strncmp(line, prefix, prefix_len) != 0)
		return (0);
	line += prefix_len;
	line = ft_skip_whitespace(line);
	if (color_check(line, &r, &g, &b) < 0)
		return (-1);
	*color = (r << 16) | (g << 8) | b;
	map_data->parsed_colors++;
	return (1);
}

int	parse_texture_path(char *line, const char *prefix, t_map_data *map_data,
		char **path)
{
	char	*start;
	char	*end;
	size_t	prefix_len;

	line = ft_skip_whitespace(line);
	prefix_len = ft_strlen(prefix);
	if (ft_strncmp(line, prefix, prefix_len) != 0)
		return (0);
	line += prefix_len;
	line = ft_skip_whitespace(line);
	if (*line == '\0' || *line == '\n')
		return (error_msg("Error: Texture path missing after prefix.\n"), -1);
	start = line;
	while (*line != '\0' && *line != '\n' && !ft_isspace((unsigned char)*line))
		line++;
	end = line;
	*path = malloc((end - start) + 1);
	if (!*path)
		return (error_msg("Error: Memory allocation failed for texture path.\n"),
			-1);
	ft_memcpy(*path, start, (end - start));
	(*path)[end - start] = '\0';
	map_data->parsed_textures++;
	printf("Parsed %s path: %s\n", prefix, *path);
	return (1);
}

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

int	parse_map_line(char **lines, t_map_data *map_data, int line_count)
{
	while (map_data->map_start_idx < line_count)
	{
		if (lines[map_data->map_start_idx]
			&& lines[map_data->map_start_idx][0] != '\n')
			break ;
		map_data->map_start_idx++;
	}
	map_data->map_rows = count_rows(lines, map_data->map_start_idx, line_count);
	map_data->map_cols = count_width(lines, map_data->map_start_idx,
			map_data->map_rows);
	map_data->map = malloc(sizeof(int *) * map_data->map_rows);
	if (!map_data->map)
		return (error_msg("Error: Memory allocation failed for map rows.\n"),
			-1);
	return (1);
}

int	parse_line(char *line, t_map_data *map_data)
{
	int	ret;

	ret = parse_texture_path(line, "NO", map_data, &map_data->no_path);
	if (ret != 0)
		return (ret);
	ret = parse_texture_path(line, "SO", map_data, &map_data->so_path);
	if (ret != 0)
		return (ret);
	ret = parse_texture_path(line, "WE", map_data, &map_data->we_path);
	if (ret != 0)
		return (ret);
	ret = parse_texture_path(line, "EA", map_data, &map_data->ea_path);
	if (ret != 0)
		return (ret);
	ret = parse_color(line, "F", map_data, &map_data->floor_color);
	if (ret != 0)
		return (ret);
	ret = parse_color(line, "C", map_data, &map_data->ceiling_color);
	if (ret != 0)
		return (ret);
	return (0);
}

int	find_next_nonblank(char **lines, int start, int line_count)
{
	int	j;

	j = start;
	while (j < line_count)
	{
		if (lines[j] && lines[j][0] != '\n')
			return (j);
		j++;
	}
	return (j);
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
		if (ret == 1)
		{
			if (map_data->parsed_textures == 4 && map_data->parsed_colors == 2)
			{
				map_data->map_start_idx = find_next_nonblank(lines, i + 1,
						line_count);
				return (parse_map_line(lines, map_data, line_count));
			}
			i++;
			continue ;
		}
		if (map_data->parsed_textures == 4 && map_data->parsed_colors == 2)
		{
			map_data->map_start_idx = find_next_nonblank(lines, i, line_count);
			return (parse_map_line(lines, map_data, line_count));
		}
		i++;
	}
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

void	print_everything_map_data(t_map_data *map_data)
{
	printf("NO Path: %s\n", map_data->no_path);
	printf("SO Path: %s\n", map_data->so_path);
	printf("WE Path: %s\n", map_data->we_path);
	printf("EA Path: %s\n", map_data->ea_path);
	printf("Floor Color: 0x%06X\n", map_data->floor_color);
	printf("Ceiling Color: 0x%06X\n", map_data->ceiling_color);
	printf("Map Start Index: %d\n", map_data->map_start_idx);
	printf("Map Rows: %zu\n", map_data->map_rows);
	printf("Map Columns: %zu\n", map_data->map_cols);
}

int	parse_cub_file(const char *filename, t_map_data *map_data)
{
	int		fd;
	int		line_count;
	char	**lines;
	int		ret;

	line_count = 0;
	if (!validate_filename(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("Error: Failed to open map file.\n"), 1);
	lines = get_all_lines(fd, &line_count);
	if (!lines)
		return (close(fd), error_msg("Error: Failed to read file lines.\n"), 1);
	debug_print_lines(lines, line_count);
	ft_memset(map_data, 0, sizeof(t_map_data));
	map_data_init(map_data);
	ret = parse_map_data(map_data, lines, line_count);
	if (ret == 0 || ret == -1)
		return (close(fd), free_lines(lines, line_count),
			free_map_data(map_data), 1);
	free_lines(lines, line_count);
	print_everything_map_data(map_data);
	return (close(fd), 0);
}
