#ifndef CUB_H
# define CUB_H

// 	---Includes---


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


typedef struct s_map
{
	char		**content;
	char 		*north;
	char 		*south;
	char 		*east;
	char 		*west;
	t_color 	floor;
	t_color 	sky;
}	t_map;

//	--- MAIN.C ---

//	--- PARSE.C ---

//	--- GAME.C ---
#endif
