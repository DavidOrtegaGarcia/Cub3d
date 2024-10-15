
#include "cub.h"

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_errorr(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void hook(void* param)
{
	const mlx_t* mlx; 
	
	mlx = param;
	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void init_game(t_map tmap)
{
	mlx_t* mlx;
	mlx_image_t *img;
	char map[4][4] = {"111", "1P1", "111"};
	(void)map;
	(void)tmap;
	// MLX allows you to define its core behaviour before startup.
	//mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (mlx == NULL)
		ft_errorr();
	/* Do stuff */

	// Create and display the image.
	img = mlx_new_image(mlx, WIDTH, 128);
	mlx_image_to_window(mlx, img, 0, 0);
	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
