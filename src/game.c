

#include "cub.h"

/*void resize_hook(int32_t width, int32_t height, void *param)
{
	mlx_image_t *img = (mlx_image_t*)param;
	mlx_resize_image(img, width, height);
}*/

void exec_game(void *param)
{
	t_mlx *tmlx;
	t_dpoint mov;


	tmlx = param; 
	mov.x = 0;
	mov.y = 0;
	mlx_delete_image(tmlx->mlx, tmlx->img);
	tmlx->img = mlx_new_image(tmlx->mlx, S_WIDTH, S_HEIGHT); // create new image
	movment_hook(tmlx, mov);
	cast_rays(tmlx); // cast the rays
	mlx_image_to_window(tmlx->mlx, tmlx->img, 0, 0);
}

double get_viwew_dir(t_mlx tmlx)
{
	if (tmlx.tmap.orientation == 'N')
		return (3 * M_PI / 2);
	if (tmlx.tmap.orientation == 'S')
		return (M_PI / 2);
	if (tmlx.tmap.orientation == 'W')
		return (M_PI);
	if (tmlx.tmap.orientation == 'E')
		return (0);
	return (0);
}

void init_tplayer(t_mlx tmlx)
{
	tmlx.tplyr->pos_px.x = tmlx.tmap.init_point.y * BOX_SIZE + BOX_SIZE / 2; //BOX_SIZE / 2 CENTRA EL JUGADOR EN MEDIO DE LA CASILLA 
	tmlx.tplyr->pos_px.y = tmlx.tmap.init_point.x * BOX_SIZE + BOX_SIZE / 2;
	tmlx.tplyr->fov_rad = (FOV * M_PI) / 180; //Convert fov to radius
	tmlx.tplyr->view_dir = get_viwew_dir(tmlx); // Orientaton of the player
}

void init_game(t_map tmap)
{
	t_mlx	tmlx;

	tmlx.tmap = tmap;
	tmlx.tplyr = (t_player *)ft_calloc(sizeof(t_player), 1);
	tmlx.tray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	tmlx.mlx = mlx_init(S_WIDTH, S_HEIGHT, "Cub3d", false);
	if (!tmlx.mlx)
		exit(EXIT_FAILURE);
	init_tplayer(tmlx);
	tmlx.img = mlx_new_image(tmlx.mlx, S_WIDTH, S_HEIGHT);
	mlx_key_hook(tmlx.mlx, &key_hook, &tmlx);
	mlx_loop_hook(tmlx.mlx, &exec_game, &tmlx);
	//mlx_resize_hook(tmlx.mlx, &resize_hook, tmlx.img);
	mlx_loop(tmlx.mlx);
	mlx_terminate(tmlx.mlx);
}
