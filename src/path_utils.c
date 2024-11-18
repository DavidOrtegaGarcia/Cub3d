#include "cub.h"

void	manage_line(t_map *map, char *line)
{
	char	**splitted;
	char *aux;

	if (!found_all(map))
	{
		aux = ft_strtrim(line, " \n");
		free(line);
		line = aux;
	}
	if (found_all(map))
		push_line(map, line);
	else if (ft_strcmp(line, "") != 0)
	{
		aux = ft_strtrim(line, " \n");
		splitted = ft_split(aux, ' ');
		free(aux);
		ft_check_element(line, splitted);
		if (is_element(splitted[0]))
			assign(map, splitted[1], is_element(splitted[0]));
		free_matrix(splitted, 2);
	}
}
