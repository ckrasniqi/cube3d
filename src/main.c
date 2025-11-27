/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckrasniq <ckrasniq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 12:35:05 by ckrasniq          #+#    #+#             */
/*   Updated: 2025/11/26 19:40:45 by ckrasniq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_randomize(void *param)
{
	t_game		*game;
	mlx_image_t	*img;

	game = param;
	if (!game)
		return ;
	img = game->image;
	if (!img)
		return ;
	for (uint32_t i = 0; i < img->width; ++i)
	{
		for (uint32_t y = 0; y < img->height; ++y)
		{
			uint32_t color = ft_pixel(rand() % 0xFF, // R
										rand() % 0xFF, // G
										rand() % 0xFF, // B
										rand() % 0xFF  // A
			);
			mlx_put_pixel(img, i, y, color);
		}
	}
}

void	ft_hook(void *param)
{
	t_game	*game;
	mlx_t	*mlx;

	game = param;
	if (!game)
		return ;
	mlx = game->mlx;
	if (!mlx)
		return ;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		game->image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		game->image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		game->image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		game->image->instances[0].x += 5;
}

void	render_map(t_map_data *map_data)
{
	for (int32_t y = 0; y < map_data->map_rows; y++)
	{
		for (int32_t x = 0; x < map_data->map_cols; x++)
		{
			if (map_data->map[y][x] == '1')
			{
				uint32_t color = ft_pixel(255, 0, 0, 255); // Red color for walls
				for (int32_t i = 0; i < TILE_SIZE; i++)
				{
					for (int32_t j = 0; j < TILE_SIZE; j++)
					{
						int32_t pixel_x = x * TILE_SIZE + i;
						int32_t pixel_y = y * TILE_SIZE + j;
						map_data->pixels[pixel_y * (map_data->map_cols * TILE_SIZE) + pixel_x] = color;
					}
				}
			}
			else
			{
				uint32_t color = ft_pixel(0, 0, 0, 255); // Black color for empty space
				for (int32_t i = 0; i < TILE_SIZE; i++)
				{
					for (int32_t j = 0; j < TILE_SIZE; j++)
					{
						int32_t pixel_x = x * TILE_SIZE + i;
						int32_t pixel_y = y * TILE_SIZE + j;
						map_data->pixels[pixel_y * (map_data->map_cols * TILE_SIZE) + pixel_x] = color;
					}
				}
			}
		}
	}
}


int	game_init(t_game *game, const char *cub_file)
{
	if (ft_memset(game, 0, sizeof(t_game)) == NULL)
		return (error_msg("initializing game structure.\n"), -1);
	if (parse_cub_file(cub_file, &game->map_data) != 1)
		return (-1);
	if (reached_maximums(&game->map_data) != 1)
		return (-1);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Game", false);
	if (!game->mlx)
	{
		free_map_data(&game->map_data);
		return (error_msg("initializing MLX.\n"), -1);
	}
	render_map(&game->map_data);
	game->image = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->image)
	{
		free_map_data(&game->map_data);
		mlx_terminate(game->mlx);
		return (error_msg("creating new image.\n"), -1);
	}
	if (mlx_image_to_window(game->mlx, game->image, 0, 0) < 0)
	{
		free_map_data(&game->map_data);
		return (error_msg("putting image to window.\n"), -1);
	}
	return (1);
}

int32_t	main(int ac, char **av)
{
	t_game		game;
	const char	*cub_file;

	if (ac != 2)
	{
		printf("Error, Usage: ./cube3d [filename].cub \n");
		return (EXIT_FAILURE);
	}
	cub_file = av[1];
	if (game_init(&game, cub_file) != 1)
		return (clean_up(&game.map_data, NULL), EXIT_FAILURE);
	mlx_loop_hook(game.mlx, ft_randomize, &game);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	free_map_data(&game.map_data);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

// // Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }
// int32_t	main(void)
// {
//
// Init mlx with a canvas size of 256x256 and the ability to resize the window.
//     mlx_t* mlx = mlx_init(256, 256, "MLX42", true);

//     if (!mlx) exit(EXIT_FAILURE);

//     // Create a 128x128 image.
//     mlx_image_t* img = mlx_new_image(mlx, 10, 10);

//
// Set the channels of each pixel in our image to the maximum byte value of 255.
//     memset(img->pixels, 255, img->width * img->height * BPP);

//     // Draw the image at coordinate (0, 0).
//     if (!img || (mlx_image_to_window(mlx, img, 20, 20) < 0))
// 		ft_error();

//     // Run the main loop and terminate on quit.
//     mlx_loop(mlx);
//     mlx_terminate(mlx);

//     return (EXIT_SUCCESS);
// }
// int32_t	main(void)
// {

// 	// MLX allows you to define its core behaviour before startup.
// 	mlx_set_setting(MLX_MAXIMIZED, true);
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
// 	if (!mlx)
// 		ft_error();

// 	/* Do stuff */

// 	// Create and display the image.
// 	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		ft_error();

// 	// Even after the image is being displayed, we can still modify the buffer.
// 	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

// 	// Register a hook and pass mlx as an optional param.
// 	// NOTE: Do this before calling mlx_loop!
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
