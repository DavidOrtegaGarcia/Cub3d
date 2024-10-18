#include "cub.h"

void	assign(t_map *map, char *path, char *element)
{
	if ((ft_strcmp(element, "NO") == 0))
		assign_north(map, path);
	else if ((ft_strcmp(element, "SO") == 0))
		assign_south(map, path);
	else if ((ft_strcmp(element, "EA") == 0))
		assign_east(map, path);
	else if ((ft_strcmp(element, "WE") == 0))
		assign_west(map, path);
	else if ((ft_strcmp(element, "F") == 0))
	{
		map->floor = get_color(&path[1]);
		if (map->check.found_floor == 1)
			ft_error("El elemento \"F\" esta repetido");
		map->check.found_floor = 1;
	}
	else if ((ft_strcmp(element, "C") == 0))
	{
		map->celling = get_color(&path[1]);
		if (map->check.found_celling == 1)
			ft_error("El elemento \"C\" esta repetido");
		map->check.found_celling = 1;
	}
}

void	assign_north(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 5, ft_strlen(path));
	if (map->check.found_north == 1)
		ft_error("El elemento \"NO\" está repetido");
	if (ft_strcmp(ext, ".xpm") == 0)
	{
		ft_error("Elemento North: La textura debe ser un archivo .xpm");
	}
	free(ext);
	path = ft_substr(path, 0, ft_strlen(path) - 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"NO\"");
	}
	map->north = path;
	map->check.found_north = 1;
	close(fd);
}

void	assign_south(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 5, ft_strlen(path));
	if (map->check.found_south == 1)
		ft_error("El elemento \"SO\" está repetido");
	if (ft_strcmp(ext, ".xpm") == 0)
	{
		ft_error("Elemento South: La textura debe ser un archivo .xpm");
	}
	free(ext);
	path = ft_substr(path, 0, ft_strlen(path) - 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"SO\"");
	}
	map->south = path;
	map->check.found_south = 1;
	close(fd);
}

void	assign_east(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 5, ft_strlen(path));
	if (map->check.found_east == 1)
		ft_error("El elemento \"EA\" está repetido");
	if (ft_strcmp(ext, ".xpm") == 0)
	{
		ft_error("Elemento East: La textura debe ser un archivo .xpm");
	}
	free(ext);
	path = ft_substr(path, 0, ft_strlen(path) - 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"EA\"");
	}
	map->east = path;
	map->check.found_east = 1;
	close(fd);
}

void	assign_west(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 5, ft_strlen(path));
	if (map->check.found_west == 1)
		ft_error("El elemento \"WE\" está repetido");
	if (ft_strcmp(ext, ".xpm") == 0)
	{
		ft_error("Elemento West: La textura debe ser un archivo .xpm");
	}
	free(ext);
	path = ft_substr(path, 0, ft_strlen(path) - 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"WE\"");
	}
	map->west = path;
	map->check.found_west = 1;
	close(fd);
}
