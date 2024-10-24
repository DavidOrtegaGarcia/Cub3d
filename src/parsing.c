#include "cub.h"

void	ft_parse(t_map *map)
{
	get_paths(map);
	show_map(map);
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