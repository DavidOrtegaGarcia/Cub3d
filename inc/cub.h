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

//	---Structures---
typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}	t_vector;

typedef struct s_point
{
	int	x;
	int	y;
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
	int			assigned_lines;
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
	xpm_t		*north;
	xpm_t		*south;
	xpm_t		*east;
	xpm_t		*west;
	t_color		floor;
	t_color		celling;
}	t_map;

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
void show_map(t_map *map);

//	--- PARSE_MAP.C ---
void push_line(t_map *map, char *line);

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

#endif