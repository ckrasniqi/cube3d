#include "cube3d.h"
#include <string.h>
#define BPP sizeof(int32_t)


// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// // Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }
int32_t	main(void)
{
    // Init mlx with a canvas size of 256x256 and the ability to resize the window.
    mlx_t* mlx = mlx_init(256, 256, "MLX42", true);

    if (!mlx) exit(EXIT_FAILURE);

    // Create a 128x128 image.
    mlx_image_t* img = mlx_new_image(mlx, 10, 10);

    // Set the channels of each pixel in our image to the maximum byte value of 255.
    memset(img->pixels, 255, img->width * img->height * BPP);

    // Draw the image at coordinate (0, 0).
    if (!img || (mlx_image_to_window(mlx, img, 20, 20) < 0))
		ft_error();

    // Run the main loop and terminate on quit.
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}
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