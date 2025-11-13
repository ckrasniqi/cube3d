/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 18:19:49 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <libft/libft.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# define WIDTH 1080
# define HEIGHT 720
# define BPP sizeof(int32_t)

typedef struct s_map_data
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			**map;
	size_t		map_rows;
	size_t		map_cols;
	int			player_start_x;
	int			player_start_y;
	double		player_start_angle;
}				t_map_data;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map_data	map_data;

}				t_game;

void			parse_map(const char *filename, t_map_data *map_data);
void			ft_error(char *error);

#endif
