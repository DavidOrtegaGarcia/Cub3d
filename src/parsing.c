#include "cub.h"

void	ft_parse(t_map *map)
{
	get_paths(map);
	ft_check_map(map);
	show_map(map);
	ft_printf("%c", map->orientation);
}

void	show_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->check.assigned_lines)
	{
		if (map->content[i])
		{
			puts(map->content[i]);
		}
		i++;
	}
}
