/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:34:49 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 13:46:03 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <string.h>

void	name_check(const char *filename)
{
	const char	*ext = ft_strrchr(filename, '.');

	if (!ext || ft_strcmp(ext, ".cub") != 0)
	{
		fprintf(stderr, "Error: Invalid file extension. Expected .cub\n");
		exit(EXIT_FAILURE);
	}
}

void	validate_sides(const char *filename)
{
	(void)filename;
}

void	validate_floor_ceiling(const char *filename)
{
	(void)filename;
}

void	validate_map_structure(const char *filename)
{
	(void)filename;
}

void	parse_map(const char *filename)
{
	name_check(filename);
	validate_sides(filename);
	validate_floor_ceiling(filename);
	validate_map_structure(filename);

	printf("Parsing map from file: %s\n", filename);
}
