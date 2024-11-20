/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:09:07 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/20 19:06:35 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
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
# define COLLISION_MARGIN 2

//	---Structures---
typedef struct s_fpoint
{
	float	x; // axis x
	float	y; // axis y
}	t_fpoint;

typedef struct s_dpoint
{
	double		x; // axis x
	double		y; // axis y
}	t_dpoint;

typedef struct s_point
{
	int		x;
	int		y;
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
	t_point				init_point;
	t_check				check;
	char				**content;
	char				orientation;
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*east;
	mlx_texture_t		*west;
	t_color				floor;
	t_color				celling;
}	t_map;

typedef struct s_player //the player structure
{
	t_point		pos_px; // player position in px
	double		view_dir; // player orientation
	float		fov_rad; // field of view in radians
	int			rot_f; // rotation flag
	int			lft_rhg_f; // left right flag
	int			up_dwn_f; // up down flag
}	t_player;

typedef struct s_ray //the ray structure
{
	double		ray_angl; // ray angle
	double		wall_dist; // distance to the wall
	int			wall_f; // flag to know if the wall is horizontal or vertical
	int			ray_num;
	t_dpoint	vertical;
	t_dpoint	horizontal;
}	t_ray;

typedef struct s_mlx //the mlx structure
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			tmap;
	t_player		*tplyr;
	t_ray			*tray;
}	t_mlx;

//	--- CHECK.C ---
void		ft_check_input(t_map *map, int argc, char *argv);
void		ft_get_doc(t_map *map, char *path, int size);
int			ft_get_rows(t_map *map, char *path);

//	--- PARSE.C ---
void		ft_parse(t_map *map);
void		show_map(t_map *map);
void		manage_line(t_map *map, char *line);

//	--- PARSE_MAP.C ---
void		push_line(t_map *map, char *line);
void		check_line(t_map *map, char *line);
void		ft_check_map(t_map *map);
void		is_position_valid(t_map *map, int y, int x);
char		*clean_line(char *line);
void		ft_error(const char *msg);

//	--- GAME.C ---
void		init_game(t_map tmap);
void		cast_rays(t_mlx *tmlx);
void		render(t_mlx *tmlx, int ray);
void		key_hook(mlx_key_data_t data_key, void *param);
void		movment_hook(t_mlx *tmlx, t_dpoint mov);
float		nor_angle(float angle);
int			my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color);
int			get_rgba(int r, int g, int b, int a);
int			reverse_bytes(int color);
t_fpoint	hor_angl(float a, float *ray_islft, t_fpoint h_itr, float *y_stp);
t_fpoint	ver_angl(float a, float *ray_islft, t_fpoint v_itr, float *x_stp);

//	--- PATHS.C ---
void		get_paths(t_map *map);
t_color		get_color(char *color);
char		*is_element(char *str);
int			found_all(t_map *map);

//	--- ASSIGN_PATHS.C ---
void		assign(t_map *map, char *path, char *element);
void		assign_north(t_map *map, char *path);
void		assign_south(t_map *map, char *path);
void		assign_east(t_map *map, char *path);
void		assign_west(t_map *map, char *path);

//	--- UTILS.C ---
char		**free_matrix(char **matrix, int i);
void		ft_error(const char *msg);
void		free_all_doc(char ***all_doc);
void		ft_check_element(char *line, char **splitted);

#endif