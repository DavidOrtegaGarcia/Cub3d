#include "cub.h"

t_map	ft_parse(char *path)
{
	t_map	map = {0};
    (void)path; 
	// puede ser mejor hacerlo con un switch y ir pasando lineas
	//map.north = get_path(ft_find_line("NO"));
	//map.south = get_path(ft_find_line("SO"));
	//map.west = get_path(ft_find_line("WE"));
	//map.east = get_path(ft_find_line("EA"));
	/* map.floor = get_color(ft_find_line("F"));
	map.celling = get_color(ft_find_line("C")); */

	// find line: 	busca una linea que quitando espacios si hay, empieze con el texto enviado
	// get_path:	extraer path de la linea
	// get_color:	extraer color de la linea

	//  map.check.check_map = find_map();
    // enviarle a partir de que linea vamos a buscar el mapa
	// map.content = fill_map();
    // enviarle checkmap

	//puede que se puedan juntar las dos funciones en una sola

	// sumarle a map.check.map_lines para saber donde empezar a contar
	return (map);
}

char	*clean_line(char *line)
{
	// 1. eliminar espacios
	// 2. comprobar caracteres permitidos: 0, 1, y SOLO UNO de los 4sentidos: NSEW
	// 3. buscar init position
    return(line);
}