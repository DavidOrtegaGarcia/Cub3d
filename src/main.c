
#include "cub.h"

int main(int argc, char *argv[])
{
	t_map map;
	
	ft_check_input(&map, argc, &argv[1]);
	
	ft_get_doc(&map, argv[1], ft_get_rows(&map, map.check.path));
	map = ft_parse(argv[1]);
	free_all_doc(&map.check.all_doc);
}