#include "cub.h"

#include "cub.h"
#include <stdlib.h>
#include <string.h>

void push_line(t_map *map, char *line)
{
    char **new_content;
    int i;

	if (!line || ft_strcmp(line, "\0") == 0)
		return;
    new_content = (char **)malloc((map->check.assigned_lines + 1) * sizeof(char *));
    if (!new_content)
        ft_error("Error al asignar memoria");
    i = 0;
    while (i < map->check.assigned_lines)
    {
        new_content[i] = map->content[i];
        i++;
    }
    new_content[i] = strdup(line);
    if (!new_content[i])
        ft_error("Error al duplicar la línea");
    free(map->content);
    map->content = new_content;
    map->check.assigned_lines++;
}
