#include "cub.h"

void ft_check_map(t_map *map)
{
    int y;
    int x;
    int rows;
    int cols;

    y = 0;
    rows = map->check.assigned_lines;
    while (y < rows)
    {
        x = 0;
        cols = ft_strlen(map->content[y]);
        while (x < cols)
        {
            if (map->content[y][x] == '0' || ft_strchr("NSWE", map->content[y][x]))
            {
                if ((y == 0 || !ft_strchr("01NSWE", map->content[y - 1][x])) ||
                    (y == rows - 1 || !ft_strchr("01NSWE", map->content[y + 1][x])) ||
                    (x == 0 || !ft_strchr("01NSWE", map->content[y][x - 1])) ||
                    (x == cols - 1 || !ft_strchr("01NSWE", map->content[y][x + 1])))
                    ft_error("El mapa no está cerrado, o contiene espacios en su interior");
            }
            x++;
        }
        y++;
    }
}

void push_line(t_map *map, char *line)
{
    char **new_content;
    int i;

	if (map->check.map_found == 0 && (!line || ft_strcmp(ft_strtrim(line, " \n"), "") == 0))
        return ;
    check_line(map, line);
    new_content = (char **)malloc((map->check.assigned_lines + 1) * sizeof(char *));
    if (!new_content)
        ft_error("Error al asignar memoria");
    i = 0;
    while (i < map->check.assigned_lines)
    {
        new_content[i] = map->content[i];
        i++;
    }
    new_content[i] = ft_strdup(line);
    map->check.map_found = 1;
    free(map->content);
    map->content = new_content;
    map->check.assigned_lines++;
}

void check_line(t_map *map, char *line)
{
    int i;
    
    i = 0;
    const char *valid_chars = "01NSWE ";
    if (!line || ft_strcmp(ft_strtrim(line, " \n"), "") == 0)
        ft_error("Una línea no puede estar vacía o solo contener espacios");
    while (line[i] != '\0')
    {
        if (!ft_strchr(valid_chars, line[i]))
            ft_error("La línea contiene caracteres no permitidos");
        if (ft_strchr("NSWE", line[i]))
        {
            if (map->check.found_init_pos)
                ft_error("Solo puede haber una posición inicial en el mapa");
            map->init_point.x = map->check.assigned_lines; // deberiamos de aclarar bien que es x y que es y
            map->init_point.y = i;
            map->check.found_init_pos = 1;
        }
        i++;
    }
}
