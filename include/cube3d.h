/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:18 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/04 18:53:31 by ckrasniq         ###   ########.fr       */
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
# include <time.h>
# include <sys/time.h>


// #define WIDTH 400
// #define HEIGHT 400

#define RED 		0xFF0000FF
#define WHITE 		0xFFFFFFFF
#define	GREEN		0x00FF00FF
#define BLACK		0x000000FF
#define	UNIT_S		72
#define UNIT_AREA	UNIT_S * UNIT_S
#define BACKGROUND	WHITE
#define	PLAYER		GREEN

# define MAX_TEXTURES 4
# define MAX_COLORS 2


typedef struct s_time
{
	double		delta_time;
	double		now;
	double		last;
	double		acc;
	double		fixed_dt;
}	t_time;

typedef struct s_settings
{
	int			tile_size;
	int			width;
	int			height;
}	t_settings;

typedef struct s_raycaster
{
	int			mapX;
	int			mapY;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	double		deltaDistX;
	double		deltaDistY;
	double		sideDistX;
	double		sideDistY;
	int			stepX;
	int			stepY;
	double		posX;
	double		posY;
	int			hit;
	int			side;
}	t_raycaster;

typedef struct s_player
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		fov;
	double		move_speed;
	double		rot_speed;
	double		rot_angle;

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


typedef struct s_resources
{
	void		*mlx;
	void		*image;
}				t_resources;

typedef struct s_game
{
	t_settings	cfg;
	t_time		time;
	t_map_data	map_data;
	t_player	player;
	t_raycaster	raycast;
	t_resources	res;

}				t_game;

//////////////////////////////////////////////////////////////////////////////
//								INITIALIZING								//
//////////////////////////////////////////////////////////////////////////////

int			struct_init(t_game *game);
int			raycaster_data_init(t_raycaster *raycast);
int			resources_init(t_resources *res);
int			time_data_init(t_time *time);
int			settings_data_init(t_settings *settings);

//////////////////////////////////////////////////////////////////////////////
//								PARSING										//
//////////////////////////////////////////////////////////////////////////////

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
int				parse_cub_file(const char *filename, t_map_data *map_data, t_game *game, t_player *p);
// void			debug_print_lines(char **lines, int line_count);

// Parsing map utils
void			set_player_direction(char identifier, t_player *player);
void			set_player_position(char identifier, t_map_data *map_data,
					int x, int y, t_player *player);
int				player_found(char c);
int				check_for_invalid_characters(char **lines,
					t_map_data *map_data, t_game *game);

// Parsing map
int				count_rows(char **lines, int start_idx, int line_count);
int				count_width(char **lines, int start_idx, int rows);
int				validate_and_save(t_map_data *map_data, t_game *game, t_player *player);
int				parse_map_line(char **lines, t_map_data *map_data,
					int line_count, t_game *game);
int				parse_map_data(t_map_data *map_data, char **lines,
					int line_count, t_game *game);

// Parsing utilities
void			map_data_init(t_map_data *map_data);
int				player_data_init(t_player *player);
int				find_next_nonblank(char **lines, int start, int line_count);
int				missing_color_texture(t_map_data *map_data);
// void			print_everything_map_data(t_map_data *map_data, char **lines, \

//////////////////////////////////////////////////////////////////////////////
//								MOVEMENT									//
//////////////////////////////////////////////////////////////////////////////

// Collision detection and movement
int				collision_detection(t_game *g, double newPosX, double newPosY);
void			move_up(t_game *g, double dirX, double dirY, double move_step);
void			move_down(t_game *g, double dirX, double dirY, double move_step);
void			move_left(t_game *g, double dirX, double dirY, double move_step);
void			move_right(t_game *g, double dirX, double dirY, double move_step);

// Movement handlers
void			handle_movement(t_game *game, double dirX, double dirY);
void			handle_rotation(t_game *game, double rot_angle,
					double rot_speed, double dt);
void			rotate_player(t_player *player, double angle);

//////////////////////////////////////////////////////////////////////////////
//								RENDERING									//
//////////////////////////////////////////////////////////////////////////////

int				render_mini_map(t_game *game, t_map_data *m);
void			draw_minimap(t_game *game, int mm_x, int mm_y, int tile, t_map_data *m);
void			draw_minimap_unit(t_game *game, int x, int y, int tile,  uint32_t color);
void			draw_player(t_game *g, int mm_x, int mm_y, int tile, double scale);
void			draw_grid2(t_game *game, int mm_x, int mm_y, int tile, t_map_data *m);

/////////////////////////////////////////////////////////////////////////////////
//							RAYCASTING										//
/////////////////////////////////////////////////////////////////////////////

void			raycaster(t_game *game, t_raycaster *rc);
void			cast_single_ray(t_game *game, t_raycaster *rc, t_settings *cfg, int x);
void			preform_dda(t_game *game, t_raycaster *rc);

// Raycaster utils
void			init_raycaster_variables(t_game *game, t_raycaster *rc, t_settings *cfg);
double			find_delta_dist(double rayDir);
void			calculate_step_and_side_dist(t_raycaster *rc);

//////////////////////////////////////////////////////////////////////////////
//							GAME SETUP									//
//////////////////////////////////////////////////////////////////////////////

int				setup_game_variables(t_game *g, t_map_data *mdata,
					t_player *player);
int				set_tile_size(int cols, int rows, int window_w, int window_h);

//////////////////////////////////////////////////////////////////////////////
//								UTILS										//
//////////////////////////////////////////////////////////////////////////////
double			get_time_seconds(void);
void			update_time(double *now, double *last, double *delta_time);
int				ft_isspace(char c);
char			*ft_skip_whitespace(const char *str);
int				not_part_of_map(char c);

// Clean up
void			free_lines(char **lines, int line_count);
void			free_map_data(t_map_data *map_data);
void			clean_up(t_map_data *map_data, char **lines);

// Error handling
void			ft_error(char *msg);
void			error_msg(const char *msg);

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
