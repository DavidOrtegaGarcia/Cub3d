
#include "cub.h"

double nor_angl(double ray_angl) // We adjust the angle value to be in range (0, 2pi).
{								// This will optimize the number of opeartions that we'll do
	if (ray_angl < 0)
		ray_angl += (2 * M_PI);
	if (ray_angl > (2 * M_PI))
		ray_angl -= (2 * M_PI);
	return (ray_angl);
}

void print_flr_cling(t_mlx *tmlx, int ray, int top_wpixel, int bot_wpixel)
{
	int	i;
	int	color;

	i = 0;
	color = get_rgba(tmlx->tmap.celling.r, tmlx->tmap.celling.g, tmlx->tmap.celling.b, 255);
	while (i < top_wpixel) // Print celling
	{
		my_put_pixel(tmlx->img, ray, i, color);
		i++;
	}
	color = get_rgba(tmlx->tmap.floor.r, tmlx->tmap.floor.g, tmlx->tmap.floor.b, 255);
	while (bot_wpixel < tmlx->mlx->height) // Print floor
	{
		my_put_pixel(tmlx->img, ray, i, color);
		bot_wpixel++;
	}
}

int	reverse_bytes(int color)
{
	unsigned int	reverse_bytes;

	reverse_bytes = 0;
	reverse_bytes |= (color & 0xFF) << 24;
	reverse_bytes |= (color & 0xFF00) << 8;
	reverse_bytes |= (color & 0xFF0000) >> 8;
	reverse_bytes |= (color & 0xFF000000) >> 24;
	return (reverse_bytes);
}

double	get_texture_x(mlx_texture_t	*texture, t_mlx *tmlx)
{
	double	texture_x;

	if (tmlx->tray->wall_f == 0) // The wall is vertical
		texture_x = (int)fmodf((tmlx->tray->vertical.y *
		(texture->width / BOX_SIZE)), texture->width);  // Sacamos el residuo de un doble con fmodf
	else // The wall is vertical
		texture_x = (int)fmodf((tmlx->tray->vertical.x *
		(texture->width / BOX_SIZE)), texture->width);
	return (texture_x);
}

mlx_texture_t	*get_texture(t_mlx *tmlx)
{
	tmlx->tray->ray_angl = nor_angl(tmlx->tray->ray_angl);
	if (tmlx->tray->wall_f == 0) // The wall is vertical
	{
		if (tmlx->tray->ray_angl > M_PI / 2 && tmlx->tray->ray_angl < 3 * (M_PI / 2))
			return (tmlx->tmap.east);
		else
			return (tmlx->tmap.west);
	}
	else // The wall is horizontal
	{
		if (tmlx->tray->ray_angl > 0 && tmlx->tray->ray_angl < M_PI)
			return (tmlx->tmap.south);
		else
			return (tmlx->tmap.north);
	}
}
  
void print_wall(t_mlx *tmlx, double wall_height, int top_wpixel, int bot_wpixel) 
{
	mlx_texture_t	*texture;
	uint32_t		*texture_pixels;
	double			scaling_factor;
	t_dpoint		texture_point;

	texture = get_texture(tmlx);
	texture_pixels = (uint32_t *)texture->pixels; // We store all the colors of the texture
	scaling_factor = (double)texture->height / wall_height; // We scale the texture to the size of the wall
	texture_point.x = get_texture_x(texture, tmlx);
	texture_point.y = (top_wpixel - (tmlx->mlx->height / 2) + (wall_height / 2)) * scaling_factor;
	if (texture_point.y < 0)
		texture_point.y = 0;
	while (top_wpixel < bot_wpixel)
	{
		my_put_pixel(tmlx->img, tmlx->tray->ray_num, top_wpixel, reverse_bytes(
			texture_pixels[(int)texture_point.y * texture->width + (int)texture_point.x]));
		texture_point.y += scaling_factor;
		top_wpixel++;
	}
}

void render(t_mlx *tmlx, int ray)
{
	double wall_height;
	double top_wpixel;
	double bot_wpixel;

	tmlx->tray->wall_dist *= cos(nor_angl(tmlx->tray->ray_angl - tmlx->tplyr->view_dir)); // fix the fisheye effect
	wall_height = (BOX_SIZE / tmlx->tray->wall_dist) * 
		((tmlx->mlx->width / 2) / tan(tmlx->tplyr->fov_rad / 2)); // get the wall height based on the distance of the wall
	top_wpixel = (tmlx->mlx->height / 2) - (wall_height / 2);
	bot_wpixel = (tmlx->mlx->height / 2) + (wall_height / 2);
	if (top_wpixel < 0) 
		top_wpixel = 0;
	if (bot_wpixel > tmlx->mlx->height)
		bot_wpixel = tmlx->mlx->height;
	tmlx->tray->ray_num = ray;
	print_wall(tmlx, wall_height, top_wpixel, bot_wpixel); 
	print_flr_cling(tmlx, ray, top_wpixel, bot_wpixel);
}
