#include "cub.h"

void    ft_check_input(t_map *map, int argc, char *argv)
{
    int len;
    char *str;
    if (argc != 2)
    {
        if (argc < 2)
            ft_error("Missing Argv");
        else
            ft_error("Multiple Argv Detected");
    }

    str = argv;
    len = (int)ft_strlen(str);
    map->check.path = str;

    if (len < 4)
        ft_error("File format error");
    else if (ft_strcmp(str + len - 4, ".cub") != 0)
        ft_error("File format error");
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
    map->check.map_lines = i;
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
    if (fd < 0) 
    {
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
	map->check.all_doc = (char **)malloc(sizeof(char *) * (i + 1));
    if (!map->check.all_doc)
        ft_error("Memory allocation failed.");
    map->check.map_lines = i;
	return (i);
}
