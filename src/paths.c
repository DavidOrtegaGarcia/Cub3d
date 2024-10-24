#include "cub.h"

void	get_paths(t_map *map)
{
	int		fd;
	char	*line;
	char	**splitted;

	//map->check.assigned_lines = 0;
	fd = open(map->check.path, O_RDONLY);
	// trimm hace malloc!!!
	while (map->check.lines_to_map < map->check.map_lines)
	{
		line = ft_strtrim(get_next_line(fd), " \n");
		if (found_all(map))
			push_line(map, ft_strtrim(line, " \n"));
		else if (ft_strcmp(line, "") != 0)
		{
			splitted = ft_split(ft_strtrim(line, " \n"), ' ');
			ft_check_element(line, splitted);
			if (is_element(splitted[0]))
				assign(map, splitted[1], is_element(splitted[0]));
		}
		map->check.lines_to_map++;
		free(line);
	}
	free_matrix(splitted, 2);
	if (found_all(map) == 0)
		ft_error("Faltan algunos elementos");
	close(fd);
}

t_color	get_color(char *color)
{
	t_color	rgb;
	char	**hex;

	hex = ft_split(color, ',');
	rgb.r = atoi(hex[0]);
	rgb.g = atoi(hex[1]);
	rgb.b = atoi(hex[2]);
	free(hex);
	return (rgb);
}

char	*is_element(char *str)
{
	if (ft_strcmp(str, "NO") == 0 || ft_strcmp(str, "SO") == 0 || \
	ft_strcmp(str, "WE") == 0 || ft_strcmp(str, "EA") == 0 || \
	ft_strcmp(str, "F") == 0 || ft_strcmp(str, "C") == 0)
		return (str);
	return (NULL);
}

int	found_all(t_map *map)
{
	if (map->check.found_north == 1 && \
	map->check.found_south == 1 && \
	map->check.found_east == 1 && \
	map->check.found_west == 1 && \
	map->check.found_floor == 1 && \
	map->check.found_celling == 1)
		return (1);
	return (0);
}

void ft_check_element(char *line, char **splitted)
{
	//trim hace malloc!!!
    int i;

    i = 0;
    if (!line || ft_strcmp(ft_strtrim(line, " \n"), "\0") == 0)
        return;
    line = ft_strtrim(line, " \n");
    if(!line | !splitted | ft_strcmp(line, "\0") == 0)
        return ;

    line = ft_strtrim(line, " \n");

    while (splitted[i])
        i++;

    if (i != 2)
        ft_error(ft_strjoin(ft_strjoin("Path \"", line), "\" not valid"));
    return ;
}
