/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/13 21:58:15 by ckrasniq         ###   ########.fr       */
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
	int			parsed_textures;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	int			parsed_colors;
	int			**map;
	int			map_start_idx;
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

// Parsing functions
void			parse_cub_file(const char *filename, t_map_data *map_data);

// Error handling
void			ft_error(char *msg);
void			error_msg(char *msg);

// Utility functions
int				ft_isspace(char c);
char			*ft_skip_whitespace(const char *str);
void			free_map_data(t_map_data *map_data);
void			free_lines(char **lines, int line_count);




#endif
