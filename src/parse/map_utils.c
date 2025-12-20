/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:53:04 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:29:03 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	set_player_dir_w(t_player *player)
{
	player->dir_x = -1.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = -0.66;
}

void	set_player_direction(char identifier, t_player *player)
{
	if (identifier == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (identifier == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (identifier == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (identifier == 'W')
		set_player_dir_w(player);
}

void	set_player_position(char identifier, int x, int y, t_game *game)
{
	t_player	*player;
	t_map_data	*m;

	player = &game->player;
	m = &game->map_data;
	player->pos_x = y;
	player->pos_y = x;
	m->map[x][y] = '0';
	set_player_direction(identifier, player);
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
				if (game->player.pos_x != -1 && game->player.pos_y != -1)
					return (error_msg("Multiple players.\n"), -1);
				set_player_position(lines[i][j], i, j, game);
			}
		}
	}
	return (1);
}
