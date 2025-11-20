/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/20 19:43:40 by ckrasniq         ###   ########.fr       */
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
# define MAX_TEXTURES 4
# define MAX_COLORS 2
# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
	char		**file_contents;
	int			line_count;
	char		**map;
	char		**map_copy;
	int			map_start_idx;
	int			map_rows;
	int			map_cols;
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


// Flood fill functions
void		flood_fill(char **map, int x, int y, t_map_data *map_data);
int				copy_map(t_map_data *map_data, int start_idx);
int				fill_map(char **lines, t_map_data *map_data);

// Parsing headers
int				reached_maximums(t_map_data *map_data);
int				color_check(char *line, int *r, int *g, int *b);
int				parse_color(char *line, const char *prefix,
					t_map_data *map_data, uint32_t *color);
int				parse_texture_path(char *line, const char *prefix,
										t_map_data *map_data, char **path);
int				parse_line(char *line, t_map_data *map_data);

// Parsing io
int				name_check(const char *filename);
int				validate_filename(const char *filename);
char			**get_all_lines(int fd, t_map_data *map_data, char **first_line);
int				parse_cub_file(const char *filename, t_map_data *map_data);
// void			debug_print_lines(char **lines, int line_count);

// Parsing map utils
void			set_player_start_position(char identifier, t_map_data *map_data,
					int x);
int				not_part_of_map(char c);
int				check_for_invalid_characters(char **lines, t_map_data *map_data);
int				save_the_map_line(char *line, int *map_row,
					t_map_data *map_data);

// Parsing map
int				count_rows(char **lines, int start_idx, int line_count);
int				count_width(char **lines, int start_idx, int rows);
int				validate_and_save(t_map_data *map_data);
int				parse_map_line(char **lines, t_map_data *map_data,
					int line_count);
int				parse_map_data(t_map_data *map_data, char **lines,
					int line_count);

// Parsing map utilities
void			map_data_init(t_map_data *map_data);
int				find_next_nonblank(char **lines, int start, int line_count);
void			print_everything_map_data(t_map_data *map_data, char **lines,
					int line_count);

// Clean up
void			free_lines(char **lines, int line_count);
void			free_map_data(t_map_data *map_data);
void			clean_up(t_map_data *map_data, char **lines);

// Error handling
void			ft_error(char *msg);
int				error_msg(const char *msg);

// Utility functions
int				ft_isspace(char c);
char			*ft_skip_whitespace(const char *str);

#endif
