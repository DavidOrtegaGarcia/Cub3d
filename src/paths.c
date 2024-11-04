#include "cub.h"

void	get_paths(t_map *map)
{
	int		fd;
	char	*line;
	char	**splitted;

	// trimm hace malloc!!!
	fd = open(map->check.path, O_RDONLY);
	while (map->check.lines_to_map < map->check.map_lines)
	{
		line = ft_strtrim(get_next_line(fd), "\n");
		if (!found_all(map))
			line = ft_strtrim(line, " \n");
		if (found_all(map))
			push_line(map, line);
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
	int		i;

	hex = ft_split(color, ',');
	if (!hex || !hex[0] || !hex[1] || !hex[2])
		ft_error("Formato de color no válido");
	rgb.r = ft_atoi(hex[0]);
	rgb.g = ft_atoi(hex[1]);
	rgb.b = ft_atoi(hex[2]);
	if ((rgb.r < 0 || rgb.r > 255) || \
	(rgb.g < 0 || rgb.g > 255) || (rgb.b < 0 || rgb.b > 255))
		ft_error("El color seleccionado no es válido");
	i = 0;
	while (hex[i] != NULL)
	{
		free(hex[i]);
		i++;
	}
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

void	ft_check_element(char *line, char **splitted)
{
	int	i;
	//trim hace malloc!!!
	i = 0;
	if (!line || ft_strcmp(ft_strtrim(line, " \n"), "\0") == 0)
		return ;
	line = ft_strtrim(line, " \n");
	if (!line | !splitted | ft_strcmp(line, "\0") == 0)
		return ;
	line = ft_strtrim(line, " \n");
	while (splitted[i])
		i++;
	if (i != 2)
		ft_error(ft_strjoin(ft_strjoin("Path \"", line), "\" not valid"));
	return ;
}
