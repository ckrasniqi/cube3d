/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_keyhooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:46:54 by msalangi          #+#    #+#             */
/*   Updated: 2025/11/20 22:33:39 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cube3d.h"

// PLAYER MOVEMENT THROUGH THE MINIMAP
// mouse hooks

int	go_back(t_game *game)
{
	int i = 0;
	int row = game->map_data.player_position_cub[0];
	int col = game->map_data.player_position_cub[1];

	if (!game->map_data.minimap_player_position)
        return (1);

	printf("walking right\n");
	printf("player position in .cub map: x: %i, y: %i\n", row, col);

	if (game->map_data.map[row][col]) // starting position of player
	{
		// move, change value
		if (game->map_data.map[row][col + 1] == 0)
		{
			game->map_data.player_position_cub[0] = row - 1; // update player position
			game->map_data.map[row][col] = 0;
			game->map_data.map[row][col + 1] = 'E';
			render_minimap(game, game->map_data);
		}
		else
			printf("there's a wall on the way!\n");
	}
	return (0);
}

int	go_right(t_game *game)
{
	int i = 0;
	int row = game->map_data.player_position_cub[0];
	int col = game->map_data.player_position_cub[1];

	if (!game->map_data.minimap_player_position)
        return (1);
	printf("walking back\n");
	printf("player position in .cub map: x: %i, y: %i\n", row, col);

	if (game->map_data.map[row][col]) // starting position of player
	{
		// move, change value
		if (game->map_data.map[row + 1][col] == 0)
		{
			game->map_data.player_position_cub[0] = row + 1; // update player position
			game->map_data.map[row][col] = 0;
			game->map_data.map[row + 1][col] = 'N';
			render_minimap(game, game->map_data);
		}
		else
			printf("there's a wall on the way!\n");
	}
	return (0);
}
int	go_left(t_game *game)
{
	int i = 0;
	int row = game->map_data.player_position_cub[0];
	int col = game->map_data.player_position_cub[1];
	
	if (!game->map_data.minimap_player_position)
        return (1);
	// while (i <= 800)
	printf("player position: x: %i, y: %i\n", game->map_data.minimap_player_position[i],  game->map_data.minimap_player_position[i + 1]);
	printf("player position in .cub map: x: %i, y: %i\n", row, col);
	if (game->map_data.map[row][col]) // starting position of player
	{
		// move, change value
		if (game->map_data.map[row - 1][col] == 0)
		{
			game->map_data.player_position_cub[0] = row - 1; // update player position
			game->map_data.map[row][col] = 0;
			game->map_data.map[row - 1][col] = 'S';	
			render_minimap(game, game->map_data);
		}
	}
	return (0);
}

int	go_forward(t_game *game)
{
	int i = 0;
	int row = game->map_data.player_position_cub[0];
	int col = game->map_data.player_position_cub[1];

	if (!game->map_data.minimap_player_position)
        return (1);
	printf("walking left\n");
	printf("player position in .cub map: x: %i, y: %i\n", row, col);

	if (game->map_data.map[row][col]) // starting position of player
	{
		// move, change value
		if (game->map_data.map[row][col - 1] == 0)
		{
			game->map_data.player_position_cub[0] = col - 1; // update player position
			game->map_data.map[row][col] = 0;
			game->map_data.map[row][col - 1] = 'W';
			render_minimap(game, game->map_data);
		}
	}
	return (0);
}

void	keys_hook(mlx_key_data_t keydata, void *g)
{
	t_game		*game = g;
	mlx_t	*mlx;

	mlx = game->mlx;
	if (!mlx || !game)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_delete_image(mlx, game->image);
		mlx_terminate(mlx);
		exit(EXIT_SUCCESS);
	}
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		go_forward(game);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		go_back(game);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		go_left(game);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		go_right(game);
}
