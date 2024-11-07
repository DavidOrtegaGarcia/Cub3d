

#include "cub.h"

//#define BPP sizeof(int32_t) //Bytes per pixel

void resize_hook(int32_t width, int32_t height, void *param)
{
	mlx_image_t *img = (mlx_image_t*)param;
	mlx_resize_image(img, width, height);
}

void exec_game(void *param)
{
	t_mlx *tmlx;

	tmlx = param; 
	mlx_delete_image(tmlx->mlx, tmlx->img);
	tmlx->img = mlx_new_image(tmlx->mlx, S_WIDTH, S_HEIGHT); // create new image
	//hook(mlx, 0, 0); // hook the player
	cast_rays(mlx); // cast the rays
	mlx_image_to_window(tmlx->mlx, tmlx->img, 0, 0);
}

void init_tplayer(t_mlx tmlx)
{
	tmlx.tplyr->pos_px.x = tmlx.tmap.init_point.x * BOX_SIZE + BOX_SIZE / 2; //BOX_SIZE / 2 CENTRA EL JUGADOR EN MEDIO DE LA CASILLA 
	tmlx.tplyr->pos_px.y = tmlx.tmap.init_point.y * BOX_SIZE + BOX_SIZE / 2;
	tmlx.tplyr->fov_rad = (FOV * M_PI) / 180; //Convert fov to radius
	tmlx.tplyr->view_dir = M_PI / 2; // Orientaton of the player
}

void init_game(t_map tmap)
{
	t_mlx	tmlx;

	tmlx.tmap = tmap;
	tmlx.tplyr = ft_calloc(-1, sizeof(t_player)); 
	tmlx.tray = ft_calloc(-1, sizeof(t_ray));
	tmlx.mlx = mlx_init(S_WIDTH, S_HEIGHT, "Cub3d", true);
	if (!tmlx.mlx)
		exit(EXIT_FAILURE);
	init_tplayer(tmlx);
	//tmlx.img = mlx_new_image(tmlx.mlx, S_WIDTH, S_HEIGHT);
	mlx_loop_hook(tmlx.mlx, &exec_game, &tmlx);
	

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
