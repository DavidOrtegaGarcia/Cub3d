
#include "cub.h"

int main(int argc, char *argv[])
{
	t_map map;
	
	ft_check_input(&map, argc, argv[1]);
	
	ft_get_doc(&map, argv[1], ft_get_rows(&map, map.check.path));
	map = ft_parse(argv[1]);
	free_all_doc(&map.check.all_doc);
}

void ft_check_input(t_map *map, int argc, char *argv[])
{
    int len;
    char *str;

    if (argc != 2) {
        if (argc < 2)
            ft_error("Missing Argv");
        else
            ft_error("Multiple Argv Detected");
    }

    str = argv[1];
    len = ft_strlen(str);
    map->check.path = str;

    if (len < 4) {
        map->check.format_error = 1;
        ft_error("File format error");
    } else if (ft_strcmp(str + len - 4, ".cub") != 0) {
        map->check.format_error = 1;
        ft_error("File format error");
    } else {
        map->check.format_error = 0;
    }
}

void ft_get_doc(t_map *map, char *path, int size)
{
    int     fd;
    char    *line;
    int     i;

    fd = open(path, O_RDONLY);
    i = 0;
    while (i < size)
	{
        line = get_next_line(fd);
        if (!line)
		{
            while (i > 0)
                free(map->check.all_doc[--i]);
            free(map->check.all_doc);
            close(fd);
            ft_error("Failed to read line from file.");
        }
        map->check.all_doc[i] = line;
        i++;
    }
    map->check.all_doc[size] = NULL;
    close(fd);
}

int	ft_get_rows(t_map *map, char *path)
{
	int		fd;
	int		i;
	char	*str;

	i = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0) {
        ft_error("Failed to open the file.");
    }
	str = get_next_line(fd);
	if (!str)
		return (-1);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	close(fd);
	map->check.all_doc = (char **)ft_malloc(sizeof(char *) * (i + 1));
    if (!map->check.all_doc)
        ft_error("Memory allocation failed.");
	return (i);
}

t_map	ft_parse(char *path)
{
	t_map	map;

	// puede ser mejor hacerlo con un switch y ir pasando lineas
	map.north = get_path(ft_find_line("NO"));
	map.south = get_path(ft_find_line("SO"));
	map.west = get_path(ft_find_line("WE"));
	map.east = get_path(ft_find_line("EA"));
	map.floor = get_color(ft_find_line("F"));
	map.celling = get_color(ft_find_line("C"));

	// find line: 	busca una linea que quitando espacios si hay, empieze con el texto enviado
	// get_path:	extraer path de la linea
	// get_color:	extraer color de la linea

	map.check.check_map = find_map(); // enviarle a partir de que linea vamos a buscar el mapa
	map.content = fill_map(); // enviarle checkmap
	//puede que se puedan juntar las dos funciones en una sola

	// sumarle a map.check.mal_lines para saber donde empezar a contar
	return (map);
}

void free_all_doc(char ***all_doc)
{
    int i = 0;

    if (!all_doc || !*all_doc)
        return;
    while ((*all_doc)[i])
	{
        free((*all_doc)[i]);
        i++;
    }
    free(*all_doc);
    *all_doc = NULL;
}

char	*clean_line(char *line)
{
	// 1. eliminar espacios
	// 2. comprobar caracteres permitidos: 0, 1, y SOLO UNO de los 4sentidos: NSEW
	// 3. buscar init position
}

void ft_error(const char *msg)
{
    ft_printf("Error: %s\n", msg);
    exit(1);
}