#include "cub.h"

void assign(t_map *map, char *path, char *element)
{
	if((ft_strcmp(element, "NO") == 0))
		assign_north(map, path); // si funciona hacemos lo mismo con todas
	else if((ft_strcmp(element, "SO") == 0))
	{
		map->south = path;
		if(map->check.found_south == 1)
			ft_error("El elemento \"SO\" esta repetido");
		map->check.found_south = 1;
	}
	else if((ft_strcmp(element, "WE") == 0))
	{
		map->west = path;
		if(map->check.found_west == 1)
			ft_error("El elemento \"WE\" esta repetido");
		map->check.found_west = 1;
	}
	else if((ft_strcmp(element, "EA") == 0))
	{
		map->east = path;
		if(map->check.found_east == 1)
			ft_error("El elemento \"EA\" esta repetido");
		map->check.found_east = 1;
	}
	else if((ft_strcmp(element, "F") == 0))
	{
		map->floor = get_color(&path[1]);
		if(map->check.found_floor == 1)
			ft_error("El elemento \"F\" esta repetido");
		map->check.found_floor = 1;
	}
	else if((ft_strcmp(element, "C") == 0))
	{
		map->celling = get_color(&path[1]);
		if(map->check.found_celling == 1)
			ft_error("El elemento \"C\" esta repetido");
		map->check.found_celling = 1;
	}
}

void assign_north(t_map *map, char *path)
{
	map->north = path;
	if(map->check.found_north == 1)
		ft_error("El elemento \"NO\" esta repetido");
	//probar textura y devolver error si no es valida
    //solo xpm y png!
	
	// si es valida la marcamos como encontrada
	map->check.found_north = 1;
}
