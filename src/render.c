

#include "cub.h"

double nor_angl(double ray_angl) // We adjust the angle value to be in range (0, 2pi).
{								// This will optimize the number of opeartions that we'll do
	if (ray_angl < 0)
		ray_angl += (2 * M_PI);
	if (ray_angl > (2 * M_PI))
		ray_angl -= (2 * M_PI);
	return (ray_angl);
}

void print_floor_ceiling(t_mlx *tmlx, int ray, int top_pixel, int bot_pixel)
{
	int	i;

	i = 0;
	while (i < top_pixel) // Print celling
	{
		my_put_pixel(&tmlx->img, ray, i, 0x89CFF3FF);
		i++;
	}
	i = bot_pixel;
	while (i < tmlx->mlx->height) // Print floor
	{
		my_put_pixel(&tmlx->img, ray, i, 0xB99470FF);
		i++;
	}
}


int get_color(t_mlx *tmlx, int flag)
{
	tmlx->tray->ray_angl = nor_angle(tmlx->tray->ray_angl); 
	if (flag == 0) // Horizontal wall
	{
		if (mlx->ray->ray_ngl > M_PI / 2 && mlx->ray->ray_ngl < 3 * (M_PI / 2))
			return (#ffe0a7); // West wall
		else
			return (#ffe0a7); // East wall
	}
	else // Vertical wall
	{
		if (mlx->ray->ray_ngl > 0 && mlx->ray->ray_ngl < M_PI)
			return (#ffe0a7); // South wall
		else
			return (#ffe0a7); // North wall
	}
}

void print_wall(t_mlx *tmlx, int ray, int top_pixel, int bot_pixel) 
{
	int color;

	color = get_color(tmlx, mlx->ray->wall_f);
	while (top_pixel < bot_pixel)
	{
		my_put_pixel(tmlx->mlx, ray, top_pixel, color);
		top_pixel++;
	}
}

void render(t_mlx *tmlx, int ray)
{
	double wall_height;
	double top_pixel;
	double bot_pixel;

	//tmlx->tray->distance *= cos(nor_angle(mlx->ray->ray_ngl - mlx->ply->angle)); // fix the fisheye effect
	wall_height = (BOX_SIZE / tmlx->tray->wall_dist) * 
		((tmlx->mlx->width / 2) / tan(tmlx->tplyr->fov_rad / 2)); // get the wall height based on the distance of the wall
	top_pixel = (tmlx->mlx->height / 2) - (wall_height / 2);
	bot_pixel = (tmlx->mlx->height / 2) + (wall_height / 2);
	if (top_pixel < 0) 
		top_pixel = 0;
	if (bot_pixel > tmlx->mlx->height)
		bot_pixel = tmlx->mlx->height;
	draw_wall(tmlx, ray, top_pixel, bot_pixel); // draw the wall
	draw_floor_ceiling(tmlx, ray, top_pixel, bot_pixel); // draw the floor and the ceiling
}
