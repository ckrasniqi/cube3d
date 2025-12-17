/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:04:16 by msalangi          #+#    #+#             */
/*   Updated: 2025/12/17 18:57:11 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

int	color_check_bonus(char *line, int *r, int *g, int *b)
{	
	if (!line || *line == '\0' || *line == '\n')
		return (-1);
	*r = ft_atoi(line);
	while (*line && *line != ',' && *line != '\n')
		line++;
	if (*line != ',')
		return (-1);
	line++;
	*g = ft_atoi(line);
	while (*line && *line != ',' && *line != '\n')
		line++;
	if (*line != ',')
		return (-1);
	line++;
	*b = ft_atoi(line);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (error_msg("Color values must be 0-255.\n"), -1);
	return (1);
}

int	parse_color_bonus(char *line, const char *prefix, t_map_data *map_data,
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
	if (color_check_bonus(line, &r, &g, &b) < 0)
		return (-1);
	*color = (r << 24) | (g << 16) | (b << 8) | 255;
	map_data->parsed_colors++;
	return (1);
}

int	parse_texture_bonus(char *line, const char *prefix, t_map_data *map_data,
		char **path)
{
	int ret = parse_color_bonus(line, "C", map_data, &map_data->ceiling_color);
	if (ret == 1)
		return(1);
	ret = parse_texture_path(line, prefix, map_data, path);
	return (ret);
}
