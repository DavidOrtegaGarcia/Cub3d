
#include "cub.h"

int	main(int argc, char *argv[])
{
	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	ft_check_input(&map, argc, argv[1]);
	map.content = malloc(sizeof(char *) * map.check.map_lines);
	ft_get_doc(&map, argv[1], ft_get_rows(&map, map.check.path));
	ft_parse(&map);
	ft_printf("%d, %d\n", map.check.assigned_lines, map.check.map_columns);
	init_game(map);
	free_all_doc(&map.check.all_doc);
}