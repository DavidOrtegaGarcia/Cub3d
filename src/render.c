/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:46 by afatir            #+#    #+#             */
/*   Updated: 2024/11/19 02:23:20 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a << 0);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	my_mlx_pixel_put(t_mlx *tmlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= tmlx->mlx->width)
		return ;
	if (y < 0)
		return ;
	else if (y >= tmlx->mlx->width)
		return ;
	mlx_put_pixel(tmlx->img, x, y, color);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/* 

double nor_angl(double ray_angl) // We adjust the angle value to be in range (0, 2pi).
{								// This will optimize the number of opeartions that we'll do
	if (ray_angl < 0)
		ray_angl += (2 * M_PI);
	if (ray_angl > (2 * M_PI))
		ray_angl -= (2 * M_PI);
	return (ray_angl);
} */

/* void	draw_floor_ceiling(t_mlx *tmlx, int ray, int t_pix, int b_pix)
{

		int	i;
	int	color;

	i = 0;
	color = get_rgba(tmlx->tmap.celling.r, tmlx->tmap.celling.g, tmlx->tmap.celling.b, 255);
	while (i < t_pix) // Print celling
	{
		my_mlx_pixel_put(tmlx, ray, i, color);
		i++;
	}
	i = b_pix;
	color = get_rgba(tmlx->tmap.floor.r, tmlx->tmap.floor.g, tmlx->tmap.floor.b, 255);
	while (i < tmlx->mlx->height) // Print floor
	{
		my_mlx_pixel_put(tmlx, ray, i, color);
		i++;
	}
} */

void	draw_floor_ceiling(t_mlx *tmlx, int ray, int t_pix, int b_pix)
{
	int	i;
	int	color;

	// Dibujar el techo
	color = get_rgba(tmlx->tmap.celling.r, tmlx->tmap.celling.g, tmlx->tmap.celling.b, 255);
	for (i = 0; i < t_pix; i++)
		my_mlx_pixel_put(tmlx, ray, i, color);

	// Dibujar el piso
	color = get_rgba(tmlx->tmap.floor.r, tmlx->tmap.floor.g, tmlx->tmap.floor.b, 255);
	for (i = b_pix; i < tmlx->mlx->height; i++)
		my_mlx_pixel_put(tmlx, ray, i, color);
}

mlx_texture_t	*get_texture(t_mlx *mlx, int flag)
{
	mlx->tray->ray_angl = nor_angle(mlx->tray->ray_angl);
	if (flag == 0)
	{
		if (mlx->tray->ray_angl > M_PI / 2 && mlx->tray->ray_angl < 3 * (M_PI / 2))
			return (mlx->tmap.east);
		else
			return (mlx->tmap.west);
	}
	else
	{
		if (mlx->tray->ray_angl > 0 && mlx->tray->ray_angl < M_PI)
			return (mlx->tmap.south);
		else
			return (mlx->tmap.north);
	}
}

/* double	get_x_o(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_o;

	if (mlx->tray->wall_f == 1)
		x_o = (int)fmodf((mlx->tray->horizontal.x * \
		(texture->width / BOX_SIZE)), texture->width);
	else
		x_o = (int)fmodf((mlx->tray->vertical.y * \
		(texture->width / BOX_SIZE)), texture->width);
	return (x_o);
} */

double	get_x_o(mlx_texture_t	*texture, t_mlx *mlx)
{
	double	x_o;

	// Ajuste para el mapeo de coordenadas de texturas
	if (mlx->tray->wall_f == 1) // Intersección horizontal
		x_o = fmod((mlx->tray->horizontal.x / BOX_SIZE) * texture->width, texture->width);
	else // Intersección vertical
		x_o = fmod((mlx->tray->vertical.y / BOX_SIZE) * texture->width, texture->width);

	// Asegurarse de que x_o esté dentro de los límites de la textura
	if (x_o < 0)
		x_o += texture->width;
	if (x_o >= texture->width)
		x_o -= texture->width;

	return (x_o);
}


void draw_wall(t_mlx *mlx, int t_pix, int b_pix, double wall_h)
{
    double x_o, y_o;
    mlx_texture_t *texture;
    uint32_t *arr;
    double factor;

    texture = get_texture(mlx, mlx->tray->wall_f);
    if (!texture || !texture->pixels)
        return ;
    arr = (uint32_t *)texture->pixels;
    factor = (double)texture->height / wall_h;
    x_o = get_x_o(texture, mlx);
    if (x_o < 0 || x_o >= (int)texture->width)
        return ;
    y_o = (t_pix - (S_HEIGHT / 2) + (wall_h / 2)) * factor;
    if (y_o < 0)
        y_o = 0;
    while (t_pix < b_pix)
    {
        if ((int)y_o >= (int)texture->height)
            break;
        my_mlx_pixel_put(mlx, mlx->tray->ray_num, t_pix, reverse_bytes(
            arr[(int)y_o * texture->width + (int)x_o]));
        y_o += factor;
        t_pix++;
    }
}


/* void	render_wall(t_mlx *mlx, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	mlx->tray->wall_dist *= cos(nor_angle(mlx->tray->ray_angl - mlx->tplyr->view_dir));
	wall_h = (BOX_SIZE / mlx->tray->wall_dist) * ((S_WIDTH / 2) / \
	tan(mlx->tplyr->fov_rad / 2));
	b_pix = (S_HEIGHT / 2) + (wall_h / 2);
	t_pix = (S_HEIGHT/ 2) - (wall_h / 2);
	if (b_pix > S_HEIGHT)
		b_pix = S_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	mlx->tray->ray_num = ray;
	draw_wall(mlx, t_pix, b_pix, wall_h);
	draw_floor_ceiling(mlx, ray, t_pix, b_pix);
} */

void render_wall(t_mlx *mlx, int ray)
{
    double wall_h;
    double t_pix, b_pix;

    // Corregir la distancia del rayo para evitar el efecto "fish-eye"
    mlx->tray->wall_dist *= cos(nor_angle(mlx->tray->ray_angl - mlx->tplyr->view_dir));

    // Calcular la altura de la pared
    wall_h = (BOX_SIZE / mlx->tray->wall_dist) * ((S_WIDTH / 2) / tan(mlx->tplyr->fov_rad / 2));

    // Calcular las posiciones superior e inferior de la pared
    t_pix = (S_HEIGHT / 2) - (wall_h / 2);
    b_pix = (S_HEIGHT / 2) + (wall_h / 2);

    // Limitar las posiciones al rango de la pantalla
    if (t_pix < 0)
        t_pix = 0;
    if (b_pix > S_HEIGHT)
        b_pix = S_HEIGHT;

    // Dibujar pared y otros elementos
    mlx->tray->ray_num = ray;
    draw_wall(mlx, t_pix, b_pix, wall_h);
    draw_floor_ceiling(mlx, ray, t_pix, b_pix);
}

