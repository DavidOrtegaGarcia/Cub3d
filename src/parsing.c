#include "cub.h"

void	ft_parse(t_map *map)
{
	get_paths(map);
	puts(map->north);
	puts(map->south);
	puts(map->west);
	puts(map->east);
	ft_printf("%d, %d, %d\n", map->celling.r, map->celling.g, map->celling.b);
	ft_printf("%d, %d, %d\n", map->floor.r, map->floor.g, map->floor.b);
	// find line: 	busca una linea que quitando espacios si hay, empieze con el texto enviado
	// get_path:	extraer path de la linea
	// get_color:	extraer color de la linea

	//  map.check.check_map = find_map();
    // enviarle a partir de que linea vamos a buscar el mapa
	// map.content = fill_map();
    // enviarle checkmap

	//puede que se puedan juntar las dos funciones en una sola

	// sumarle a map.check.map_lines para saber donde empezar a contar
	//return (map);
}

char	*clean_line(char *line)
{
	// 1. eliminar espacios
	// 2. comprobar caracteres permitidos: 0, 1, y SOLO UNO de los 4sentidos: NSEW
	// 3. buscar init position
    return(line);
}