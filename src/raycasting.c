#include "cub.h"

int wall_hit(t_mlx *tmlx, double x, double y)
{
	t_point map_pos;

	map_pos.x = floor(x / BOX_SIZE); // get the x position in the map
	map_pos.y = floor(y / BOX_SIZE); // get the y position in the map

	if (tmlx->tmap.content[map_pos.y] != 0 && map_pos.x <= (int)ft_strlen(tmlx->tmap.content[map_pos.y])) 
		if (tmlx->tmap.content[map_pos.y][map_pos.x] == '1') 
			return (1);  
	return (0);
}

int unit_circle(double ray_angl, char axis) 
{
	if (axis == 'x')
	{
		if (ray_angl > 0 && ray_angl < M_PI) // The ray is facing up (negative axis)
		return (1);
	}
	else if (axis == 'y')
	{
		if (ray_angl > (M_PI / 2) && ray_angl < (3 * M_PI) / 2) // The ray is facing left (negative axis)
		return (1);
	}
	return (0); //The ray is facing down or right (Positive axis)
}

// Detrminate the direction of the ray and adjust inter and step variables consquently
int check_inter(double ray_angl, double *inter, double *step, int is_horizon)
{
	if (is_horizon == 1)
	{
		if (ray_angl > 0 && ray_angl < M_PI) // Check if the ray aims down 
		{
			*inter += BOX_SIZE;  // NOTE: The coordinate system used in 2D graphics works the opposite of the Cartesian system 
								// on the y axis, therefore to go down we increment y axis instead of decrement it
			return (-1); // Ray facing down 
		}
		*step *= -1; // We will decrement y axis insteat of increment it to go rigth
	}
	else
	{
		if (!(ray_angl > M_PI / 2 && ray_angl < 3 * M_PI / 2)) // Check if the ray aims right 
		{
			*inter += BOX_SIZE;
			return (-1); // Ray facing right
		}
		*step *= -1; // We will decrement x axis insteat of increment it to go left
	}
	return (1); // Ray aims up or left
}

double get_dist_ver_w(t_mlx *tmlx, double ray_angl) // get the vertical intersection
{
	// An intersection is the point between the ray we cast and the edge of one of the boxes that conforms the map
	t_dpoint v_inter;
	double x_step;
	double y_step;
	int  x_ray_dir; // Variable used to decied if the ray is proyected left or right

	x_step = BOX_SIZE; 
	y_step = BOX_SIZE * tan(ray_angl);
	v_inter.x = floor(tmlx->tplyr->pos_px.x / BOX_SIZE) * BOX_SIZE;
	v_inter.y = tmlx->tplyr->pos_px.y + (v_inter.x - tmlx->tplyr->pos_px.x) * tan(ray_angl);
	x_ray_dir = check_inter(ray_angl, &v_inter.x, &x_step, 0); 
	if ((unit_circle(ray_angl, 'x') == 1 && y_step < 0) ||
		(unit_circle(ray_angl, 'x') == 0 && y_step > 0)) // We adjusts the direction by determining to move up or down.
		y_step *= -1;
	while (wall_hit(tmlx, v_inter.x - x_ray_dir, v_inter.y) == 0)
	{
		v_inter.x += x_step;
		v_inter.y += y_step;
	}
	tmlx->tray->vertical.x = v_inter.x;
	tmlx->tray->vertical.y = v_inter.y;
	return (sqrt(pow(v_inter.x - tmlx->tplyr->pos_px.x, 2) + 
			pow(v_inter.y - tmlx->tplyr->pos_px.y, 2))); // get the distance (Pythagoras’s theorem (a2 + b2 = c2))
}

double get_dist_hor_w(t_mlx *tmlx, double ray_angl)
{
	// An intersection is the point between the ray we cast and the edge of one of the boxes that conforms the map
	t_dpoint h_inter;
	double x_step;
	double y_step;
	int  y_ray_dir; // Variable used to decied if the ray is proyected up or down

	y_step = BOX_SIZE; // Vertical distance bettween every intersection point we check (diference between y coordinate)
	x_step = BOX_SIZE / tan(ray_angl); // Horizontal distance bettween every intersection point we check (diference between x coordinate)
	h_inter.y = floor(tmlx->tplyr->pos_px.y / BOX_SIZE) * BOX_SIZE; // We use floor to make sure the point is in the right border (y) of the start box (round down the number)
	h_inter.x = tmlx->tplyr->pos_px.x + (h_inter.y - tmlx->tplyr->pos_px.y) / tan(ray_angl); // We put the point on the superior border(x) of the start box based on the ray_angl
	y_ray_dir = check_inter(ray_angl, &h_inter.y, &y_step, 1);
	if ((unit_circle(ray_angl, 'y') == 1 && x_step > 0) ||
		(unit_circle(ray_angl, 'y') == 0 && x_step < 0)) // We adjusts the direction by determining to move left or right.
		x_step *= -1;
	while (wall_hit(tmlx, h_inter.x, h_inter.y - y_ray_dir) == 0) 
	{
		h_inter.x += x_step;
		h_inter.y += y_step;
	}
	tmlx->tray->horizontal.x = h_inter.x;
	tmlx->tray->horizontal.y = h_inter.y;
	return (sqrt(pow(h_inter.x - tmlx->tplyr->pos_px.x, 2) +
			pow(h_inter.y - tmlx->tplyr->pos_px.y, 2))); // get the distance (Pythagoras’s theorem (a2 + b2 = c2))
}


void cast_rays(t_mlx *tmlx)
{
	double dist_hor_w; 
	double dist_ver_w;
	int  ray;

	ray = 0; // Number of rays (we have to cast one per every pixel in our resolution)
	tmlx->tray->ray_angl = tmlx->tplyr->view_dir - (tmlx->tplyr->fov_rad / 2); // the start angle (Player view direction - Field of view)
	while (ray < tmlx->mlx->width)
	{
		tmlx->tray->wall_f = 0; // Flag to know if the wall is horizontal or vertical
		dist_hor_w = get_dist_hor_w(tmlx, nor_angl(tmlx->tray->ray_angl)); // get the distance to the closest horizontal wall 
		dist_ver_w = get_dist_ver_w(tmlx, nor_angl(tmlx->tray->ray_angl)); // get the distance to the closest vertical wall
		if (dist_ver_w <= dist_hor_w) // get the distance to the closest wall
			tmlx->tray->wall_dist = dist_ver_w;
		else
		{
			tmlx->tray->wall_dist = dist_hor_w;
			tmlx->tray->wall_f = 1;
		}
		render(tmlx, ray);
		ray++;
		tmlx->tray->ray_angl += (tmlx->tplyr->fov_rad / tmlx->mlx->width); // We get the next projection angle to render (this value is got in realtion of our position in the map)
										   								   // Actual angle + Field of view / Width of the resolution
		
	}
}
