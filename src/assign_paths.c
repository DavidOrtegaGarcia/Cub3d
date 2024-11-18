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

void print_texture(mlx_texture_t *texture) {
    if (texture == NULL) {
        printf("Texture is NULL\n");
        return;
    }

    printf("Texture info:\n");
    printf("Width: %u\n", texture->width);
    printf("Height: %u\n", texture->height);
    printf("Bytes per pixel: %u\n", texture->bytes_per_pixel);

    // Imprimir los primeros 10 píxeles (o toda la textura si es pequeña)
    printf("First 10 pixels:\n");
    for (unsigned int i = 0; i < 10 && i < texture->width * texture->height; i++) {
        uint8_t *pixel = &texture->pixels[i * texture->bytes_per_pixel];
        // Dependiendo del formato de píxel (por ejemplo, ARGB o RGB), ajusta el formato de salida
        if (texture->bytes_per_pixel == 4) { // Supongamos ARGB
            printf("Pixel %u: 0x%02x%02x%02x%02x\n", i, pixel[0], pixel[1], pixel[2], pixel[3]);
        } else if (texture->bytes_per_pixel == 3) { // Supongamos RGB
            printf("Pixel %u: 0x%02x%02x%02x\n", i, pixel[0], pixel[1], pixel[2]);
        } else {
            printf("Pixel %u: Unknown format\n", i);
        }
    }
}


void	assign_north(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 4, ft_strlen(path));
	if (map->check.found_north == 1)
		ft_error("El elemento \"NO\" está repetido");
	if (ft_strcmp(ext, ".png") != 0)
	{
		ft_error("Elemento North: La textura debe ser un archivo .png");
	}
	free(ext);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"NO\"");
	}
	map->north = mlx_load_png(path);
	print_texture(map->north);
	map->check.found_north = 1;
	close(fd);
}

void	assign_south(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 4, ft_strlen(path));
	if (map->check.found_south == 1)
		ft_error("El elemento \"SO\" está repetido");
	if (ft_strcmp(ext, ".png") != 0)
	{
		ft_error("Elemento South: La textura debe ser un archivo .png");
	}
	free(ext);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"SO\"");
	}
	map->south = mlx_load_png(path);
	print_texture(map->south);
	map->check.found_south = 1;
	close(fd);
}

void	assign_east(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 4, ft_strlen(path));
	if (map->check.found_east == 1)
		ft_error("El elemento \"EA\" está repetido");
	if (ft_strcmp(ext, ".png") != 0)
	{
		ft_error("Elemento East: La textura debe ser un archivo .png");
	}
	free(ext);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"EA\"");
	}
	map->east = mlx_load_png(path);
	print_texture(map->east);
	map->check.found_east = 1;
	close(fd);
}

void	assign_west(t_map *map, char *path)
{
	char	*ext;
	int		fd;

	fd = 0;
	ext = ft_substr(path, ft_strlen(path) - 4, ft_strlen(path));
	if (map->check.found_west == 1)
		ft_error("El elemento \"WE\" está repetido");
	if (ft_strcmp(ext, ".png") != 0)
	{
		ft_error("Elemento West: La textura debe ser un archivo .png");
	}
	free(ext);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		ft_error("Error al abrir la ruta de la textura \"WE\"");
	}
	map->west = mlx_load_png(path);
	print_texture(map->west);
	map->check.found_west = 1;
	close(fd);
}
