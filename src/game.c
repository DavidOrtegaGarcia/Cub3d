/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:13:17 by daortega          #+#    #+#             */
/*   Updated: 2024/10/22 15:33:10 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"
//#define BPP sizeof(int32_t) //Bytes per pixel

int	my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return (1);
	mlx_put_pixel(img, x, y, color);
	return (0);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// Print the window width and height.
/*static void hook(void* param)
{
	const mlx_t* mlx; 
	
	mlx = param;
	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}*/
void resize_hook(int32_t width, int32_t height, void* param)
{
	mlx_image_t *img = (mlx_image_t*)param;
	mlx_resize_image(img, width, height);
}

void init_game(t_map tmap)
{
	(void)tmap;
	t_mlx	tmlx;
	uint32_t y;
	uint32_t x;
	y = 0;

	tmlx.mlx = mlx_init(S_WIDTH, S_HEIGHT, "Cub3d", true);
	if (!tmlx.mlx)
		exit(EXIT_FAILURE);
	tmlx.img = mlx_new_image(tmlx.mlx, S_WIDTH, S_HEIGHT);
	
	//Insertar pixeles
	/*mlx_image_to_window(tmlx.mlx, tmlx.img, 0, 0);
	while (y < tmlx.img->height / 2)
	{
		x = 0;
		while (x < tmlx.img->width / 2)
		{
			my_put_pixel(tmlx.img, x, y,  get_rgba(tmap.celling.r, 
			tmap.celling.g, tmap.celling.b, 255));
			x++;
		}
		y++;
	}*/
	//mlx_loop_hook(mlx, &hook, mlx);
	mlx_resize_hook(tmlx.mlx, &resize_hook, tmlx.img);
	mlx_loop(tmlx.mlx);
	mlx_terminate(tmlx.mlx);
}
