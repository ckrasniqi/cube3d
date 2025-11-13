/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:34:49 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 21:15:49 by ckrasniq         ###   ########.fr       */
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

int	parse_color(char *line, const char *prefix, uint32_t *color)
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
	printf("Parsed %s color: %d,%d,%d\n", prefix, r, g, b);
	return (1);
}

int	parse_texture_path(char *line, const char *prefix, char *path)
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
	start = line;
	while (*line != '\0' && *line != '\n' && !ft_isspace(*line))
		line++;
	end = line;
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

int	parse_line(char *line, t_map_data *map_data)
{
	if (line == NULL || map_data == NULL)
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_path(line, "NO", map_data->no_path),
			map_data->parsed_textures++);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_path(line, "SO", map_data->no_path),
			map_data->parsed_textures++);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_path(line, "WE", map_data->we_path),
			map_data->parsed_textures++);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_path(line, "EA", map_data->ea_path),
			map_data->parsed_textures++);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line, "F", &map_data->floor_color),
			map_data->parsed_colors++);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line, "C", &map_data->ceiling_color),
			map_data->parsed_colors++);
	else
	{
		// Handle map lines here in the future
	}
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
	// if (ft_strchr(line, '1') || ft_strchr(line, '0')
	// 		|| ft_strchr(line, 'N') || ft_strchr(line, 'S')
	// 		|| ft_strchr(line, 'E') || ft_strchr(line, 'W'))
	// 	{
	// 		// parse_map()
	// 	}
	if (line)
		free(line);
	close(fd);
	return (0);
}

void	parse_cub_file(const char *filename, t_map_data *map_data)
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
