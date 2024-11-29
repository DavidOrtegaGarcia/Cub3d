
#include "cub.h"

int	main(int argc, char *argv[])
{

	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	ft_check_input(&map, argc, argv[1]);
	ft_get_doc(&map, argv[1], ft_get_rows(&map, map.check.path));
	ft_parse(&map);
	(void)argc;
	(void)argv;
  
	t_map 	tmap;
	t_color floor;
	t_color celling;
	char north[23] = "../resources/wall1.xpm";
	char south[23] = "../resources/wall2.xpm";
	char east[23] = "../resources/wall3.xpm";
	char west[23] = "../resources/wall4.xpm";

	floor.r = 93;
	floor.g = 97;
	floor.b = 94;

	celling.r = 89;
	celling.g = 30;
	celling.r = 30;

	tmap.north = mlx_load_xpm42(north);;
	tmap.south = mlx_load_xpm42(south);;
	tmap.east = mlx_load_xpm42(east);;
	tmap.west = mlx_load_xpm42(west);;
	tmap.floor = floor;
	tmap.celling = celling; 
	init_game(tmap);
	free_all_doc(&map.check.all_doc);
}