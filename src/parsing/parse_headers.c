/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:40:59 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/12 17:35:22 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	reached_maximums(t_map_data *map_data)
{
	if (map_data->parsed_colors > 2
		|| map_data->parsed_textures > 4)
		return (error_msg("Exceeded maximum number of textures or colors.\n"),
			-1);
	if (map_data->parsed_colors == 2 && map_data->parsed_textures == 4
		&& map_data->no_path && map_data->so_path && map_data->we_path
		&& map_data->ea_path)
		return (1);
	return (0);
}

int	color_check(char *line, int *r, int *g, int *b)
{
	if (!line || *line == '\0' || *line == '\n')
		return (error_msg("Color values missing.\n"), -1);
	*r = ft_atoi(line);
	while (*line && *line != ',' && *line != '\n')
		line++;
	if (*line != ',')
		return (error_msg("Invalid color format (missing 1st comma).\n"), -1);
	line++;
	*g = ft_atoi(line);
	while (*line && *line != ',' && *line != '\n')
		line++;
	if (*line != ',')
		return (error_msg("Invalid color format (missing 2nd comma).\n"), -1);
	line++;
	*b = ft_atoi(line);

	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (error_msg("Color values must be 0-255.\n"), -1);
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
	*color = (r << 24) | (g << 16) | (b << 8) | 255;
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
		return (error_msg("Texture path missing after prefix.\n"), -1);
	start = line;
	while (*line != '\0' && !ft_isspace((unsigned char)*line))
		line++;
	end = line;
	*path = malloc((end - start) + 1);
	if (!*path)
		return (error_msg("Memory allocation failed.\n"), -1);
	ft_memcpy(*path, start, (end - start));
	(*path)[end - start] = '\0';
	map_data->parsed_textures++;
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
