/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:44:33 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/20 17:28:45 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_paths(t_map *map)
{
	int		fd;
	char	*aux;
	char	*line;

	fd = open(map->check.path, O_RDONLY);
	while (map->check.lines_to_map < map->check.map_lines)
	{
		aux = get_next_line(fd);
		if (!aux)
			break ;
		line = ft_strtrim(aux, " \n");
		free(aux);
		manage_line(map, line);
		map->check.lines_to_map++;
		free(line);
	}
	if (found_all(map) == 0)
		ft_error("Faltan algunos elementos");
	close(fd);
}

t_color	get_color(char *color)
{
	t_color	rgb;
	char	**hex;
	int		i;

	i = 0;
	hex = ft_split(color, ',');
	if (!hex || !hex[0] || !hex[1] || !hex[2])
		ft_error("Formato de color no válido");
	while (hex[i])
		i++;
	if (i != 3)
		ft_error("At least one color is not valid");
	rgb.r = ft_atoi(hex[0]);
	rgb.g = ft_atoi(hex[1]);
	rgb.b = ft_atoi(hex[2]);
	if ((rgb.r < 0 || rgb.r > 255) || \
	(rgb.g < 0 || rgb.g > 255) || (rgb.b < 0 || rgb.b > 255))
		ft_error("El color seleccionado no es válido");
	free_matrix(hex, i);
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
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strtrim(line, " \n");
	if (!line || !splitted || ft_strcmp(aux, "\0") == 0)
		return ;
	while (splitted[i])
		i++;
	if (i != 2)
		ft_error("At least one path is not valid");
	free(aux);
}
