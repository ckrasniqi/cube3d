/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalangi <msalangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:05 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/12/20 23:28:43 by msalangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cube3d.h"

void	ft_hook(void *param)
{
	t_game	*g;

	g = param;
	if (mlx_is_key_down(g->res.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->res.mlx);
	update_time(&g->time.now, &g->time.last, &g->time.delta_time);
	handle_rotation(g, g->player.rot_speed);
	handle_movement(g, g->player.dir_x, g->player.dir_y);
	handle_hand(g);
	raycaster(g, &g->raycast);
	render_mini_map(g, &g->map_data);
}

int	game_init(t_game *game, const char *cub_file)
{
	if (struct_init(game) == -1)
		return (error_msg("Initializing game structure.\n"), -1);
	if (parse_cub_file(cub_file, &game->map_data, game, &game->player) != 1)
		return (-1);
	if (reached_maximums(&game->map_data) == -1)
		return (-1);
	if (init_textures(&game->map_data, &game->res) == -1)
		return (-1);
	setup_game_variables(game, &game->map_data, &game->player);
	game->res.mlx = mlx_init(game->cfg.width, game->cfg.height, "Game", false);
	if (!game->res.mlx)
		return (error_msg("Initializing MLX.\n"), -1);
	game->res.image = mlx_new_image(game->res.mlx,
			game->cfg.width, game->cfg.height);
	if (!game->res.image)
		return (error_msg("Creating new image.\n"), -1);
	if (mlx_image_to_window(game->res.mlx, game->res.image, 0, 0) < 0)
		return (error_msg("Putting image to window.\n"), -1);
	if (render_mini_map(game, &game->map_data) == -1)
		return (error_msg("Rendering mini-map.\n"), -1);
	return (1);
}

int	main(int ac, char **av)
{
	t_game		game;
	const char	*cub_file;

	if (ac != 2)
	{
		error_msg("Usage: ./cube3d [filename].cub \n");
		return (EXIT_FAILURE);
	}
	cub_file = av[1];
	if (game_init(&game, cub_file) != 1)
		return (clean_up(&game.map_data, NULL), EXIT_FAILURE);
	mlx_loop_hook(game.res.mlx, ft_hook, &game);
	mlx_loop(game.res.mlx);
	free_map_data(&game.map_data);
	mlx_terminate(game.res.mlx);
	return (EXIT_SUCCESS);
}
