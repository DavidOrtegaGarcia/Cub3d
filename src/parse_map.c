#include "cub.h"

void	is_position_valid(t_map *map, int y, int x)
{
	int	rows;
	int	cols;

	rows = map->check.assigned_lines;
	cols = ft_strlen(map->content[y]);
	if (y == 0 || x >= (int)ft_strlen(map->content[y - 1]) || \
		!ft_strchr("01NSWE", map->content[y - 1][x]))
		ft_error("El mapa no está debidamente cerrado.");
	if (y == rows - 1 || x >= (int)ft_strlen(map->content[y + 1]) || \
		!ft_strchr("01NSWE", map->content[y + 1][x]))
		ft_error("El mapa no está debidamente cerrado.");
	if (x == 0 || !ft_strchr("01NSWE", map->content[y][x - 1]))
		ft_error("El mapa no está debidamente cerrado.");
	if (x == cols - 1 || !ft_strchr("01NSWE", map->content[y][x + 1]))
		ft_error("El mapa no está debidamente cerrado.");
}

void	ft_check_map(t_map *map)
{
	int	y;
	int	x;
	int	rows;
	int	cols;

	y = 0;
	rows = map->check.assigned_lines;
	while (y < rows)
	{
		x = 0;
		cols = ft_strlen(map->content[y]);
		while (x < cols)
		{
			if (map->content[y][x] == '0' || \
			ft_strchr("NSWE", map->content[y][x]))
				is_position_valid(map, y, x);
			x++;
		}
		y++;
	}
}

void	push_line(t_map *map, char *line)
{
	char	**new_content;
	int		i;
	if (map->check.map_found == 0 && \
	(!line || ft_strcmp(ft_strtrim(line, " \n"), "") == 0))
		return ;
	check_line(map, line);
	i = map->check.assigned_lines + 1;
	new_content = (char **)malloc((i) * sizeof(char *));
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
	//free(map->content);
	if(map->content)
		free_matrix(map->content, map->check.assigned_lines);
	map->content = new_content;
	free_matrix(new_content, i);
	map->check.assigned_lines++;
}

void	check_line(t_map *map, char *line)
{
	int		i;
	char	*valid_chars;
	char 	*aux;

	valid_chars = "01NSWE ";
	i = 0;
	aux = ft_strtrim(line, " \n");
	if (!line || ft_strcmp(aux, "") == 0)
		ft_error("Una línea no puede estar vacía o solo contener espacios");
	while (line[i] != '\0')
	{
		if (!ft_strchr(valid_chars, line[i]))
			ft_error("La línea contiene caracteres no permitidos");
		if (ft_strchr("NSWE", line[i]))
		{
			if (map->check.found_init_pos)
				ft_error("Solo puede haber una posición inicial en el mapa");
			map->init_point.x = map->check.assigned_lines;
			map->init_point.y = i;
			map->orientation = line[i];
			map->check.found_init_pos = 1;
		}
		i++;
	}
	free(aux);
}
