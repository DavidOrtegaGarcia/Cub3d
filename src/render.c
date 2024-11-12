

#include "cub.h"

void render(t_mlx *tmlx)
{
	double wall_height;
	double top_pixel;
	double bot_pixel;

	//tmlx->tray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye effect
	wall_height = (BOX_SIZE / tmlx->tray->wall_dist) * 
		((tmlx->mlx->width / 2) / tan(tmlx->tplyr->fov_rad / 2)); // get the wall height
	top_pixel = (tmlx->mlx->height / 2) - (wall_height / 2);
	bot_pixel = (tmlx->mlx->height / 2) + (wall_height / 2);
	if (top_pixel < 0) 
		top_pixel = 0;
	if (bot_pixel > tmlx->mlx->height)
		bot_pixel = tmlx->mlx->height;
	//draw_wall(mlx, ray, t_pix, b_pix); // draw the wall
	//draw_floor_ceiling(mlx, ray, t_pix, b_pix); // draw the floor and the ceiling
}
