/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/14 14:46:38 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "MLX42/MLX42.h"
# include <fcntl.h>
# include <libft/libft.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
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
int				parse_cub_file(const char *filename, t_map_data *map_data);

// Parsing headers
int				parse_line(char *line, t_map_data *map_data);
int				color_check(char *line, int *r, int *g, int *b);
int				parse_texture_path(char *line, const char *prefix,
					t_map_data *map_data, char **path);
int				parse_color(char *line, const char *prefix,
					t_map_data *map_data, uint32_t *color);

// Parsing io
int				parse_cub_file(const char *filename, t_map_data *map_data);
char			**get_all_lines(int fd, int *line_count);
void			debug_print_lines(char **lines, int line_count);
int				validate_filename(const char *filename);
int				name_check(const char *filename);

// Parsing map
size_t	count_rows(char **lines, int start_idx, int line_count);
size_t	count_width(char **lines, int start_idx, size_t rows);
int		parse_map_line(char **lines, t_map_data *map_data, int line_count);
int		parse_map_data(t_map_data *map_data, char **lines, int line_count);
int		find_next_nonblank(char **lines, int start, int line_count);

// Parsing utilities
void			map_data_init(t_map_data *map_data);
void			print_everything_map_data(t_map_data *map_data);



// Error handling
void			ft_error(char *msg);
void			error_msg(char *msg);

// Utility functions
int				ft_isspace(char c);
char			*ft_skip_whitespace(const char *str);
void			free_map_data(t_map_data *map_data);
void			free_lines(char **lines, int line_count);

#endif
