/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:49:03 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/17 19:11:08 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	free_checks(t_map_data *map_data)
{
	if (map_data->pixels)
		free(map_data->pixels);
	if (map_data->no_path)
		free(map_data->no_path);
	if (map_data->so_path)
		free(map_data->so_path);
	if (map_data->we_path)
		free(map_data->we_path);
	if (map_data->ea_path)
		free(map_data->ea_path);
	if (map_data->ceiling_path)
		free(map_data->ceiling_path);
}

void	free_lines(char **lines, int line_count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < line_count)
	{
		if (lines[i])
			free(lines[i]);
		i++;
	}
	free(lines);
}

void	free_map_data(t_map_data *map_data)
{
	int	i;

	if (!map_data)
		return ;
	free_checks(map_data);
	if (map_data->map)
	{
		i = 0;
		while (i < map_data->map_rows)
		{
			if (map_data->map[i])
				free(map_data->map[i]);
			i++;
		}
		free(map_data->map);
	}
	ft_memset(map_data, 0, sizeof(t_map_data));
}

void	clean_up(t_map_data *map_data, char **lines)
{
	free_map_data(map_data);
	free_lines(lines, -1);
}
