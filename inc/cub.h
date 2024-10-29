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

//	---Structures---
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
	char		**check_map;
	int			init_pos_found;
	int			lines_to_map;
	int			map_lines;
	int			map_columns;
	int			found_north;
	int			found_south;
	int			found_west;
	int			found_east;
	int			found_floor;
	int			found_celling;
}	t_check;

typedef struct s_map
{
	t_point		init_point;
	t_check		check;
	char		**content;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	t_color		floor;
	t_color		celling;
	t_point		p_plyr;
}	t_map;

typedef struct s_player //the player structure
{
	int  p_x; // player x position in pixels
	int  p_y; // player y position in pixels	
	double angle; // player angle
	float fov_rad; // field of view in radians
	int  rot; // rotation flag
	int  lft_rhg_f; // left right flag
	int  up_dwn_f; // up down flag
}	t_player;

typedef struct s_ray //the ray structure
{
 double ray_angl; // ray angle
 double distance; // distance to the wall
 int  flag;  // flag for the wall
}	t_ray;

typedef struct s_mlx //the mlx structure
{
	mlx_t		*mlx; // the mlx pointer
	mlx_image_t	*img; // the image
	t_map		tmap; 
	t_player	*tplayer;
	t_ray		*tray; 
}	t_mlx;
//	--- MAIN.C ---

//	--- GAME.C ---
void	init_game(t_map tmap);

//	--- CHECK.C ---
void	ft_check_input(t_map *map, int argc, char *argv);
void	ft_get_doc(t_map *map, char *path, int size);
int		ft_get_rows(t_map *map, char *path);

//	--- PARSE.C ---
void	ft_parse(t_map *map);
char	*clean_line(char *line);
void	ft_error(const char *msg);

//	--- GAME.C ---
void init_game(t_map tmap);

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

#endif