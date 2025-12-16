/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:33:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/16 20:32:44 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

uint32_t get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0x000000FF);
	index = (y * texture->width + x) * 4;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

int	load_texture(const char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		error_msg("Failed to load texture.\n");
		return (-1);
	}
	return (1);
}

int	init_textures(t_map_data *map_data, t_resources *res)
{
	if (load_texture(map_data->no_path, &res->wall_textures[TEX_NORTH]) != 1)
		return (-1);
	if (load_texture(map_data->so_path, &res->wall_textures[TEX_SOUTH]) != 1)
		return (-1);
	if (load_texture(map_data->we_path, &res->wall_textures[TEX_WEST]) != 1)
		return (-1);
	if (load_texture(map_data->ea_path, &res->wall_textures[TEX_EAST]) != 1)
		return (-1);
	if (load_texture(map_data->ceiling_path, &res->ceiling_texture) != 1)
		return (-1);
	return (1);
}
