#include "cub.h"

void	ft_parse(t_map *map)
{
	map->check.map_found = 0;
	get_paths(map);
	show_map(map);
}

void show_map(t_map *map)
{
    int i;

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

char	*clean_line(char *line)
{
	// 1. eliminar espacios
	// 2. comprobar caracteres permitidos: 0, 1, y SOLO UNO de los 4sentidos: NSEW
	// 3. buscar init position
    return(line);
}