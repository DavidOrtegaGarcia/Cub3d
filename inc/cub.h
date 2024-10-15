#ifndef CUB_H
# define CUB_H

// 	---Includes---
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h> 
# include "../mlx_42/include/MLX42/MLX42.h"

//	---Structures---
typedef struct s_vector
{
	int x;
	int y;
	int z;
}	t_vector;

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

//	--- MAIN.C ---

//	--- PARSE.C ---
void	ft_check_input(t_map *map, int argc, char *argv[]);
void	ft_get_doc(t_map *map, char *path, int size);
int		ft_get_rows(t_map *map, char *path);
t_map	ft_parse(char *path);
char	*clean_line(char *line);

//	--- GAME.C ---
void init_game(t_map tmap);

//	--- ERROR_FREE.C ---
void free_all_doc(char ***all_doc);
void ft_error(const char *msg);

#endif