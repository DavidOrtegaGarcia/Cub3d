#include "cub.h"

void get_paths(t_map *map)
{
	int		fd;
	char    *line;
	//necesitamos que este numero sea dinamico!!!
	map->check.map_lines = 15;
    //hay que inicializar las variables de control!!!
    map->check.found_north = 0;
	fd = open(map->check.path, O_RDONLY);
    while (map->check.lines_to_map < map->check.map_lines)
	{
        line = get_next_line(fd);
		if(ft_strcmp(ft_split(line, ' ')[0], "NO") == 0)
			assign(map, ft_split(line, ' ')[1], "NO");
		else if(ft_strcmp(ft_split(line, ' ')[0], "SO") == 0)
			assign(map, ft_split(line, ' ')[1], "SO");
		else if(ft_strcmp(ft_split(line, ' ')[0], "WE") == 0)
			assign(map, ft_split(line, ' ')[1], "WE");
		else if(ft_strcmp(ft_split(line, ' ')[0], "EA") == 0)
			assign(map, ft_split(line, ' ')[1], "EA");
		else if(ft_strcmp(ft_split(line, ' ')[0], "F") == 0)
			assign_colors(map, ft_split(line, ' ')[1], "F");
		else if(ft_strcmp(ft_split(line, ' ')[0], "C") == 0)
			assign_colors(map, ft_split(line, ' ')[1], "C");
		map->check.lines_to_map++;
	}
	if (found_all(map) == 0)
		ft_error("Faltan algunos elementos");
	close(fd);
}

void assign_colors(t_map *map, char *path, char *element)
{
	if((ft_strcmp(element, "F") == 0))
	{
		map->floor = get_color(path);
		if(map->check.found_floor == 1)
			ft_error("El elemento \"F\" esta repetido");
		map->check.found_floor = 1;
	}
	else if((ft_strcmp(element, "C") == 0))
	{
		map->celling = get_color(path);
		if(map->check.found_celling == 1)
			ft_error("El elemento \"C\" esta repetido");
		map->check.found_celling = 1;
	}
}

void assign(t_map *map, char *path, char *element)
{
	if((ft_strcmp(element, "NO") == 0))
	{
		map->north = path;
		if(map->check.found_north == 1)
			ft_error("El elemento \"NO\" esta repetido");
		map->check.found_north = 1;
	}
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
}

int found_all(t_map *map)
{
	if(map->check.found_north == 1 && \
	 map->check.found_south == 1 && \
	 map->check.found_east == 1 && \
	 map->check.found_west == 1 && \
	 map->check.found_floor == 1 && \
	 map->check.found_celling == 1) 
		return(1);
	return(0);
}

t_color get_color(char *color)
{
	t_color rgb;
	char **hex;

	hex = ft_split(color, ',');	
	rgb.r = atoi(hex[0]);
	rgb.g = atoi(hex[1]);
	rgb.b = atoi(hex[2]);
	return (rgb);
}