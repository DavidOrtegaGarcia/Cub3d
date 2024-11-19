/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:36:01 by afatir            #+#    #+#             */
/*   Updated: 2024/11/19 16:32:00 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int unit_circle(float ray_angl, char axis) 
{
	if (axis == 'x')
	{
		if (ray_angl > 0 && ray_angl < M_PI) // The ray is facing up (negative axis)
		return (1);
	}
	else if (axis == 'y')
	{
		if (ray_angl > (M_PI / 2) && ray_angl < (3 * M_PI) / 2) // The ray is facing left (negative axis)
		return (1);
	}
	return (0); //The ray is facing down or right (Positive axis)
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += BOX_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += BOX_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_mlx *mlx)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / BOX_SIZE);
	y_m = floor (y / BOX_SIZE);
	if ((y_m >= mlx->tmap.check.assigned_lines || x_m >= mlx->tmap.check.map_columns))
		return (0);
	if (mlx->tmap.content[y_m] && x_m <= (int)ft_strlen(mlx->tmap.content[y_m]))
		if (mlx->tmap.content[y_m][x_m] == '1')
			return (0);
	return (1);
}

float get_h_inter(t_mlx *mlx, float angl)
{
    float h_x, h_y;
    float x_step, y_step;

    // Calcular la primera intersección horizontal
    h_y = floor(mlx->tplyr->pos_px.y / BOX_SIZE) * BOX_SIZE;

    // Ajustar hacia arriba o hacia abajo según la dirección del rayo
    if (angl > 0 && angl < M_PI)  // Rayo hacia abajo
        h_y += BOX_SIZE;          // El rayo va hacia abajo, entonces se suma BOX_SIZE
    else                           // Rayo hacia arriba
        h_y -= 1;                 // El rayo va hacia arriba, entonces se resta 1

    // Calcular x inicial basándonos en la intersección y
    h_x = mlx->tplyr->pos_px.x + (h_y - mlx->tplyr->pos_px.y) / tan(angl);

    // Definir pasos
    y_step = (angl > 0 && angl < M_PI) ? BOX_SIZE : -BOX_SIZE;  // Ajuste de y_step según la dirección
    x_step = BOX_SIZE / tan(angl); // Paso en el eje X según el ángulo

    // Ajustar el signo de x_step según la dirección del rayo
    if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0))
        x_step *= -1;

    // Iterar hasta encontrar una pared
    while (wall_hit(h_x, h_y, mlx))
    {
        h_x += x_step; // Actualizar posición de x
        h_y += y_step; // Actualizar posición de y
    }

    // Guardar las coordenadas de la intersección
    mlx->tray->horizontal.x = h_x;
    mlx->tray->horizontal.y = h_y;

    return sqrt(pow(h_x - mlx->tplyr->pos_px.x, 2) + pow(h_y - mlx->tplyr->pos_px.y, 2)); // Devolver la distancia
}



float get_v_inter(t_mlx *mlx, float angl)
{
    float v_x, v_y;
    float x_step, y_step;

    // Calcular la primera intersección vertical
    v_x = floor(mlx->tplyr->pos_px.x / BOX_SIZE) * BOX_SIZE;

    // Ajustar hacia la derecha o izquierda según la dirección del rayo
    if (!(angl > M_PI / 2 && angl < 3 * M_PI / 2)) // Rayo hacia la derecha
        v_x += BOX_SIZE;
    else                                          // Rayo hacia la izquierda
        v_x -= 1;

    // Calcular y inicial basándonos en la intersección x
    v_y = mlx->tplyr->pos_px.y + (v_x - mlx->tplyr->pos_px.x) * tan(angl);

    // Definir pasos
    x_step = (angl > M_PI / 2 && angl < 3 * M_PI / 2) ? -BOX_SIZE : BOX_SIZE;
    y_step = BOX_SIZE * tan(angl);

    // Ajustar el signo de y_step según la dirección del rayo
    if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0))
        y_step *= -1;

    // Iterar hasta encontrar una pared
    while (wall_hit(v_x - ((angl > M_PI / 2 && angl < 3 * M_PI / 2) ? 1 : 0), v_y, mlx))
    {
        v_x += x_step;
        v_y += y_step;
    }

    // Guardar coordenadas de la intersección
    mlx->tray->vertical.x = v_x;
    mlx->tray->vertical.y = v_y;

    return sqrt(pow(v_x - mlx->tplyr->pos_px.x, 2) + pow(v_y - mlx->tplyr->pos_px.y, 2));
}

void	cast_rays(t_mlx *mlx)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	mlx->tray->ray_angl = mlx->tplyr->view_dir - (mlx->tplyr->fov_rad / 2);
	while (ray < S_WIDTH)
	{
		
		h_inter = get_h_inter(mlx, nor_angle(mlx->tray->ray_angl));
		v_inter = get_v_inter(mlx, nor_angle(mlx->tray->ray_angl));
		if (v_inter <= h_inter)
		{
			mlx->tray->wall_dist = v_inter;
			mlx->tray->wall_f = 0;
		}
		else
		{
			mlx->tray->wall_dist = h_inter;
			mlx->tray->wall_f = 1;
		}
		render_wall(mlx, ray);
		ray++;
		mlx->tray->ray_angl += (mlx->tplyr->fov_rad / S_WIDTH);
	}
}
