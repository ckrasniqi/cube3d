/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:53:04 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/28 15:47:03 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	set_player_start_position(char identifier, t_map_data *m, int x, int y, t_player player)
{
	player.px = x;
	player.py = y;
	player.fov = 60.0;
	player.move_speed = 0.1;
	player.rot_speed = 5.0;
	m->map[y][x] = '0';
	m->minimap_player_position = malloc(2 * sizeof(int));
	if (m->minimap_player_position)
	{
		m->minimap_player_position[0] = x;
		m->minimap_player_position[1] = y;
	}
	m->player_position_cub[0] = y;
	m->player_position_cub[1] = x;
	if (identifier == 'N')
		player.angle = 270.0;
	else if (identifier == 'S')
		player.angle = 90.0;
	else if (identifier == 'E')
		player.angle = 0.0;
	else if (identifier == 'W')
		player.angle = 180.0;
}

int	player_found(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_for_invalid_characters(char **lines, t_map_data *m, t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < m->map_rows)
	{
		j = -1;
		while (++j < m->map_cols)
		{
			if (not_part_of_map(lines[i][j]))
				return (error_msg("Invalid character in map.\n"), -1);
			else if (player_found(lines[i][j]))
			{
				if (m->player_start_x != -1 && m->player_start_y != -1)
					return (error_msg("Multiple players.\n"), \
							-1);
				set_player_start_position(lines[i][j], m, i, j, game->player);
			}
		}
	}
	return (1);
}
