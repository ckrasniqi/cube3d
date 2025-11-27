/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 23:07:03 by msalangi          #+#    #+#             */
/*   Updated: 2025/11/27 16:37:32 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

// -> array of 800 integers. each % 2 is x


void	save_player_position(t_map_data *map, int x, int y)
{
	static int i = 0;

	if (i < UNIT_AREA * 2)
	{
		map->minimap_player_position[i] = x;
		// printf("player unit position saved in [%i]: x = %i\n", i, map->minimap_player_position[i]);
		i++;
		map->minimap_player_position[i] = y;
		// printf("player unit position saved in [%i]: y = %i\n", i, map->minimap_player_position[i]);
	}
	i++;
}

int	render_player(t_game *game, int row, int i, int col, int j)
{
	if (i > 5 && j > 5)
		mlx_put_pixel(game->image, row + i, col + j, PLAYER);
	else
		mlx_put_pixel(game->image, row + i, col + j, BACKGROUND);
	return (0);
}

// row & col are pixel positions in the window, offset changes in render_minimap
int	draw_unit(t_game *game, t_map_data map, int row, int col, char unit_value)
{
	size_t	i;
	size_t	j;
	size_t	color;

	i = 0;
	j = 0;
	if (unit_value == '1') // WALL UNIT
		color = RED;
	else if (unit_value == '0') // FLOOR UNIT
		color = WHITE;
	else if (unit_value == 'N' || unit_value == 'S' || unit_value == 'W' || unit_value == 'E') // PLAYER UNIT
		color = GREEN;
	else
		return (1);
	while (i <= UNIT_S)
	{
		while (j <= UNIT_S)
		{
			if (color != GREEN)
				mlx_put_pixel(game->image, row + i, col + j, color);
			else if (color == GREEN)
			{
				render_player(game, row, i, col, j);
				save_player_position(&map, row + i, col + j);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	render_minimap(t_game *game, t_map_data	map)
{
	size_t	i;
	size_t	j;
	int		row;
	int		col;

	i = 0;
	j = 0;
	// row = UNIT_S;
	// col = UNIT_S;
	row = 0;
	col = 0;
	// read map[i][j] unit and draw it
	while (i < map.map_rows)
	{
		while (j < map.map_cols)
		{
			char unit_value = map.map[i][j];
			if (unit_value == 'N' || unit_value == 'S' || unit_value == 'W' || unit_value == 'E')
			{
				game->map_data.player_position_cub[0] = i;
				game->map_data.player_position_cub[1] = j;
			}
			// printf("value of current unit: %i\n", unit_value);
			if (draw_unit(game, map, row, col, unit_value))
				return (1);
			j++;
			col += UNIT_S;
		}
		i++;
		row += UNIT_S;
		j = 0;
		// col = UNIT_S;
		col = 0;
	}
	draw_grid(game->map_data, game);
	find_player(game);
	return (0);
}


// TEST STUFF

int main(void)
{
    t_game      game;
    t_map_data  map;
    char         **arr;

	map.map_rows = 15;
	map.map_cols = 15;

	arr = malloc(sizeof(char *) * map.map_rows + 1);
	arr[map.map_rows] = NULL;
	for (size_t i = 0; i < map.map_rows; i++)
	{
    	arr[i] = malloc(sizeof(char) * map.map_cols + 1);
		arr[i][map.map_cols] = '\0';
	}

	char tmp[15][15] = {
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
    {'1','N','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','1','0','1','1','1','1','1','1','1','0','1','0','1'},
    {'1','0','0','0','1','0','0','0','0','0','1','0','0','0','1'},
    {'1','1','1','0','1','0','1','1','1','0','1','0','1','1','1'},
    {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','1'},
    {'1','0','1','1','1','0','1','0','1','0','1','1','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','0','1','0','1','1','1','1','1','1','1','0','1','0','1'},
    {'1','0','0','0','1','0','0','0','0','0','1','0','0','0','1'},
    {'1','1','1','0','1','0','1','1','1','0','1','0','1','1','1'},
    {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','1'},
    {'1','0','1','1','1','0','1','0','1','0','1','1','1','0','1'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
	};

	for (size_t r = 0; r < map.map_rows; r++)
	{
   		for (size_t c = 0; c < map.map_cols; c++)
        	arr[r][c] = tmp[r][c];
	}
	map.map = arr;
	map.minimap_player_position = malloc(sizeof(int) * UNIT_AREA * 2);
	if (!map.minimap_player_position)
	{
		perror("malloc fail");
		return (1);
	}
	game.map_data = map;

    game.mlx = mlx_init(WIDTH, HEIGHT, "minimap test", false);
    game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game.mlx, game.image, 0, 0);
    render_minimap(&game, map);
	mlx_key_hook(game.mlx, &keys_hook, &game);
	// mlx_key_hook(game.mlx, &arrow_hook, &game);
    mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

    return (0);
}


  // map.map_rows = 4;
    // map.map_cols = 4;

    // arr = malloc(sizeof(int *) * map.map_rows);
    // for (size_t i = 0; i < map.map_rows; i++)
    //     arr[i] = malloc(sizeof(int) * map.map_cols);

    //     1111
    //     1N01
    //     1001
    //     1111

    // arr[0][0] = 1; arr[0][1] = 1; arr[0][2] = 1; arr[0][3] = 1;
    // arr[1][0] = 1; arr[1][1] = 'N'; arr[1][2] = 0; arr[1][3] = 1;
    // arr[2][0] = 1; arr[2][1] = 0; arr[2][2] = 0; arr[2][3] = 1;
    // arr[3][0] = 1; arr[3][1] = 1; arr[3][2] = 1; arr[3][3] = 1;

    // map.map = arr;