/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/28 15:46:51 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// #define WIDTH 400
// #define HEIGHT 400

#define RED 		0xFF0000FF
#define WHITE 		0xFFFFFFFF
#define	GREEN		0x00FF00FF
#define	UNIT_S		72
#define UNIT_AREA	UNIT_S * UNIT_S
#define BACKGROUND	WHITE
#define	PLAYER		GREEN

# define MAX_TEXTURES 4
# define MAX_COLORS 2


typedef struct s_player
{
	double		px;
	double		py;
	double		angle;
	double		fov;
	double		move_speed;
	double		rot_speed;

}				t_player;

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
	char		**map;
	char		**map_copy;
	int			line_count;
	int			map_start_idx;
	int			map_rows;
	int			map_cols;
	uint32_t	*pixels;

	int			*minimap_player_position;
	int			player_position_cub[2];

}				t_map_data;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_map_data	map_data;
	t_player	player;
	int			width;
	int			height;
	int			tile_size;

	/* added: time of previous frame for smooth movement */
	double		last_time;

}				t_game;

// Flood fill functions
int				ft_is_map_closed(char **map, int x, int y, t_map_data *m);
int				copy_map(t_map_data *map_data, int start_idx);

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
char			**get_all_lines(char const *filename, t_map_data *map_data);
int				parse_cub_file(const char *filename, t_map_data *map_data, t_game *game);
// void			debug_print_lines(char **lines, int line_count);

// Parsing map utils
void			set_player_start_position(char identifier, t_map_data *map_data,
					int x, int y, t_player player);
int				player_found(char c);
int				check_for_invalid_characters(char **lines,
					t_map_data *map_data, t_game *game);

// Parsing map
int				count_rows(char **lines, int start_idx, int line_count);
int				count_width(char **lines, int start_idx, int rows);
int				validate_and_save(t_map_data *map_data, t_game *game);
int				parse_map_line(char **lines, t_map_data *map_data,
					int line_count, t_game *game);
int				parse_map_data(t_map_data *map_data, char **lines,
					int line_count, t_game *game);

// Parsing utilities
void			map_data_init(t_map_data *map_data);
int				find_next_nonblank(char **lines, int start, int line_count);
int				missing_color_texture(t_map_data *map_data);
void			print_everything_map_data(t_map_data *map_data, char **lines,
					int line_count);

// Clean up
void			free_lines(char **lines, int line_count);
void			free_map_data(t_map_data *map_data);
void			clean_up(t_map_data *map_data, char **lines);

// Error handling
void			ft_error(char *msg);
void			error_msg(const char *msg);

// Utility functions
void			*ft_realloc(void *ptr, size_t new_size);
int				ft_isspace(char c);
char			*ft_skip_whitespace(const char *str);
int				not_part_of_map(char c);

//////////////////////////////////////////////////////////////////////////////
// 								RENDERING									//
//////////////////////////////////////////////////////////////////////////////

int				render_minimap(t_game *game, t_map_data	map);
void			keys_hook(mlx_key_data_t keydata, void *param);
void			arrow_hook(mlx_key_data_t keydata, void *g);
int				draw_grid(t_map_data map_data, t_game *game);
int				draw_rows(t_map_data map_data, t_game *game);
void			find_player(t_game *game);

#endif
