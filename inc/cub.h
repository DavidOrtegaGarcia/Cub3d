#ifndef CUB_H
# define CUB_H

// 	---Includes---
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include "libft.h" 
# include "../mlx_42/include/MLX42/MLX42.h"

// --Macros MLX-- 
# define S_WIDTH 1920 //Screen width
# define S_HEIGHT 1080 //Screen heigth
# define BOX_SIZE 30 // Box size
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed

//	---Structures---
/*typedef struct s_vector
{
	int x;
	int y;
	int z;
}	t_vector;*/

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_check
{
	// inicializar todos los errores posibles
	int			format_error;
	int			path_error;
	int			invalid_character_error;
	int			map_design_error;
	int			no_init_pos_error;
	int			duplicate_init_pos_error;
	int			no_walls_error;

	// inicializar todos los datos necesarios
	// para el check pero no para el programa
	char		*path;
	char		**all_doc;
	char		**check_map;
	int			init_pos_found;
	int			lines_to_map;
	int			map_lines;
	int			map_columns;
}	t_check;

typedef struct s_map
{
	t_check		check;
	char		**content;
	char 		*north;
	char 		*south;
	char 		*east;
	char 		*west;
	t_color 	floor;
	t_color 	celling;
}	t_map;

typedef struct s_player //the player structure
{
	int  plyr_x; // player x position in pixels
	int  plyr_y; // player y position in pixels	
	double angle; // player angle
	float fov_rd; // field of view in radians
	int  rot; // rotation flag
	int  l_r; // left right flag
	int  u_d; // up down flag
}	t_player;

typedef struct s_ray //the ray structure
{
 double ray_ngl; // ray angle
 double distance; // distance to the wall
 int  flag;  // flag for the wall
}	t_ray;

typedef struct s_data //the data structure
{
	int  p_x;  // player x position in the map
	int  p_y;  // player y position in the map
	int  w_map;  // map width
	int  h_map;  // map height
} t_data;

typedef struct s_mlx //the mlx structure
{
	mlx_image_t	*img; // the image
	mlx_t		*mlx; // the mlx pointer
	//t_ray		tray; // the ray structure
	t_data		tdata; // the data structure
	//t_player	tply; // the player structure
} t_mlx;
//	--- MAIN.C ---

//	--- PARSE.C ---
void	ft_check_input(t_map *map, int argc, char *argv[]);
void	ft_get_doc(t_map *map, char *path, int size);
int		ft_get_rows(t_map *map, char *path);
t_map	ft_parse(char *path);
char	*clean_line(char *line);
void	ft_error(const char *msg);

//	--- GAME.C ---
void init_game(t_map tmap);
#endif