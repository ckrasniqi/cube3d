/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 22:53:04 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/26 18:18:12 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	set_player_start_position(char identifier, t_map_data *m, int x, int y)
{
	m->player_start_x = x;
	if (identifier == 'N' || identifier == 'S')
		m->player_start_y = y;
	else if (identifier == 'E' || identifier == 'W')
		m->player_start_y = y;
	if (identifier == 'N')
		m->player_start_angle = 3 * M_PI / 2;
	else if (identifier == 'S')
		m->player_start_angle = M_PI / 2;
	else if (identifier == 'E')
		m->player_start_angle = 0.0;
	else if (identifier == 'W')
		m->player_start_angle = M_PI;
}

int	player_found(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	check_for_invalid_characters(char **lines, t_map_data *m)
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
							1);
				set_player_start_position(lines[i][j], m, i, j);
			}
		}
	}
	return (1);
}

int	replace_spaces_with_zeros(char *row)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(row);
	while (j < len)
	{
		if (row[j] == ' ')
			row[j] = '0';
		j++;
	}
	return (len);
}

int	pad_row_with_zeros(char **row, int len, int cols)
{
	char	*new;
	int		j;

	new = ft_calloc(cols + 1, sizeof(char));
	if (!new)
		return (error_msg("Memory allocation failed.\n"), -1);
	j = 0;
	while (j < len)
	{
		new[j] = (*row)[j];
		j++;
	}
	while (j < cols)
	{
		new[j] = '0';
		j++;
	}
	free(*row);
	*row = new;
	return (1);
}
