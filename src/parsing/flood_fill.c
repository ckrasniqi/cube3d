/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:42:43 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 22:43:15 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	flood_fill_map_borders(char **lines, t_map_data *map_data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map_data->map_rows)
	{
		j = 0;
		while (j < map_data->map_cols)
		{
			if (i == 0 || i == map_data->map_rows - 1 || j == 0
				|| j == map_data->map_cols - 1)
			{
				if (lines[map_data->map_start_idx + i][j] != '1'
					&& lines[map_data->map_start_idx + i][j] != ' ')
				{
					lines[map_data->map_start_idx + i][j] = 'F';
				}
			}
			j++;
		}
		i++;
	}
}
