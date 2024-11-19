#include "cub.h"

int wall_hit(t_mlx *tmlx, double x, double y)
{
	t_point map_pos;

	if (x < 0 || y < 0)
		return (0);
	map_pos.x = (int)floor(x / BOX_SIZE); // get the x position in the map
	map_pos.y = (int)floor(y / BOX_SIZE); // get the y position in the map

	if ((map_pos.y >= tmlx->tmap.check.assigned_lines || map_pos.x >= tmlx->tmap.check.map_columns))
		return (0);
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
	int  x#ifndef CUB_H
# define CUB_H

// 	---Includes---
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include "libft.h" 
# include "../mlx_42/include/MLX42/MLX42.h"

// --Macros MLX-- 
# define S_WIDTH 1920 //Screen width
# define S_HEIGHT 1080 //Screen heigth
# define BOX_SIZE 30 // Box size
# define FOV 60 // field of view
# define ROTATION_SPD 0.045 // rotation speed
# define PLAYER_SPD 4 // player speed

//	---Structures---
typedef struct s_fpoint
{
	float x; // axis x
	float y; // axis y
}	t_fpoint;

typedef struct s_dpoint
{
	double x; // axis x
	double y; // axis y
}	t_dpoint;

typedef struct s_point
{
	int x;
	int y;
}	t_point;


typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_check
{
	char		*path;
	char		**all_doc;
	int			found_init_pos;
	int			lines_to_map;
	int			map_lines;
	int			assigned_lines;
	int			map_columns;
	int			found_north;
	int			found_south;
	int			found_west;
	int			found_east;
	int			found_floor;
	int			found_celling;
	int			map_found;
}	t_check;

typedef struct s_map
{
	t_point		init_point;
	t_check		check;
	char		**content;
	char		orientation;
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*east;
	mlx_texture_t		*west;
	t_color		floor;
	t_color		celling;
}	t_map;

typedef struct s_player //the player structure
{
	t_point pos_px; // player position in px
	double	view_dir; // player orientation
	float	fov_rad; // field of view in radians
	int		rot_f; // rotation flag
	int		lft_rhg_f; // left right flag
	int		up_dwn_f; // up down flag
}	t_player;

typedef struct s_ray //the ray structure
{
	double	ray_angl; // ray angle
	double	wall_dist; // distance to the wall
	int		wall_f;  // flag to know if the wall is horizontal or vertical
	int 	ray_num;
	t_dpoint vertical;
	t_dpoint horizontal;
}	t_ray;

typedef struct s_mlx //the mlx structure
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		tmap; 
	t_player	*tplyr;
	t_ray		*tray; 
}	t_mlx;

//	--- MAIN.C ---



//	--- CHECK.C ---
void	ft_check_input(t_map *map, int argc, char *argv);
void	ft_get_doc(t_map *map, char *path, int size);
int		ft_get_rows(t_map *map, char *path);

//	--- PARSE.C ---
void	ft_parse(t_map *map);

void	show_map(t_map *map);

void	manage_line(t_map *map, char *line);

//	--- PARSE_MAP.C ---
void	push_line(t_map *map, char *line);
void	check_line(t_map *map, char *line);
void	ft_check_map(t_map *map);
void	is_position_valid(t_map *map, int y, int x);

char	*clean_line(char *line);
void	ft_error(const char *msg);

//	--- GAME.C ---
void init_game(t_map tmap);
void cast_rays(t_mlx *tmlx);
void render(t_mlx *tmlx, int ray);
void	key_hook(mlx_key_data_t data_key, void *param);
void	movment_hook(t_mlx *tmlx, t_dpoint mov);
float	nor_angle(float angle);
int		my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color);
int 	get_rgba(int r, int g, int b, int a);


/* archivo castigado */
//void	render_wall(t_mlx *mlx, int ray);
//void	my_mlx_pixel_put(t_mlx *tmlx, int x, int y, int color);



//	--- PATHS.C ---
void	get_paths(t_map *map);
t_color	get_color(char *color);
char	*is_element(char *str);
int		found_all(t_map *map);

//	--- ASSIGN_PATHS.C ---
void	assign(t_map *map, char *path, char *element);
void	assign_north(t_map *map, char *path);
void	assign_south(t_map *map, char *path);
void	assign_east(t_map *map, char *path);
void	assign_west(t_map *map, char *path);

//	--- UTILS.C ---
char	**free_matrix(char **matrix, int i);
void	ft_error(const char *msg);
void	free_all_doc(char ***all_doc);
void		ft_check_element(char *line, char **splitted);

#endif_ray_dir; // Variable used to decied if the ray is proyected left or right

	x_step = BOX_SIZE; 
	y_step = BOX_SIZE * tan(ray_angl);
	v_inter.x = floor(tmlx->tplyr->pos_px.x / BOX_SIZE) * BOX_SIZE;
	v_inter.y = tmlx->tplyr->pos_px.y + (v_inter.x - tmlx->tplyr->pos_px.x) * tan(ray_angl);
	x_ray_dir = check_inter(ray_angl, &v_inter.x, &x_step, 0); 
	if ((unit_circle(ray_angl, 'x') == 1 && y_step < 0) ||
		(unit_circle(ray_angl, 'x') == 0 && y_step > 0)) // We adjusts the direction by determining to move up or down.
		y_step *= -1;
	while (v_inter.x >= 0 && v_inter.y >=0 && wall_hit(tmlx, v_inter.x - x_ray_dir, v_inter.y) == 0)
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

	x_step = BOX_SIZE; // Vertical distance bettween every intersection point we check (diference between y coordinate)
	y_step = BOX_SIZE / tan(ray_angl); // Horizontal distance bettween every intersection point we check (diference between x coordinate)
	h_inter.x = floor(tmlx->tplyr->pos_px.x / BOX_SIZE) * BOX_SIZE; // We use floor to make sure the point is in the right border (y) of the start box (round down the number)
	h_inter.y = tmlx->tplyr->pos_px.y + (h_inter.x - tmlx->tplyr->pos_px.x) / tan(ray_angl); // We put the point on the superior border(x) of the start box based on the ray_angl
	y_ray_dir = check_inter(ray_angl, &h_inter.x, &x_step, 1);
	if ((unit_circle(ray_angl, 'y') == 1 && x_step > 0) ||
		(unit_circle(ray_angl, 'y') == 0 && x_step < 0)) // We adjusts the direction by determining to move left or right.
		x_step *= -1;
	while (h_inter.x >= 0 && h_inter.y >= 0 && wall_hit(tmlx, h_inter.x, h_inter.y - y_ray_dir) == 0) 
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
		{
			tmlx->tray->wall_dist = dist_ver_w;
			tmlx->tray->wall_f = 0; // Flag to know if the wall is horizontal or vertical
		}
		else
		{
			tmlx->tray->wall_dist = dist_hor_w;
			tmlx->tray->wall_f = 1;
		}
		render_wall(tmlx, ray);
		ray++;
		tmlx->tray->ray_angl += (tmlx->tplyr->fov_rad / tmlx->mlx->width); // We get the next projection angle to render (this value is got in realtion of our position in the map)
										   								   // Actual angle + Field of view / Width of the resolution
		
	}
}
