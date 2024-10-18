#include "cub.h"

void	get_paths(t_map *map)
{
	int		fd;
	char	*line;
	char	**splitted;

	fd = open(map->check.path, O_RDONLY);
	while (map->check.lines_to_map < map->check.map_lines)
	{
		line = get_next_line(fd);
		splitted = ft_split(line, ' ');
		if (is_element(splitted[0]))
			assign(map, splitted[1], is_element(splitted[0]));
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
