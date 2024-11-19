/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:36:01 by afatir            #+#    #+#             */
/*   Updated: 2024/11/19 21:42:26 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	wall_hit(t_mlx *mlx, float x, float y)
{
	t_point	map_pos;

	if (x < 0 || y < 0)
		return (0);
	map_pos.x = floor (x / BOX_SIZE);
	map_pos.y = floor (y / BOX_SIZE);
	if ((map_pos.y >= mlx->tmap.check.assigned_lines \
	|| map_pos.x >= mlx->tmap.check.map_columns))
		return (0);
	if (mlx->tmap.content[map_pos.y] && map_pos.x <= \
	(int)ft_strlen(mlx->tmap.content[map_pos.y]))
		if (mlx->tmap.content[map_pos.y][map_pos.x] == '1')
			return (0);
	return (1);
}

int	unit_circle(float ray_angl, char axis)
{
	if (axis == 'x')
	{
		if (ray_angl > 0 && ray_angl < M_PI)
			return (1);
	}
	else if (axis == 'y')
	{
		if (ray_angl > (M_PI / 2) && ray_angl < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

float	get_dist_ver_w(t_mlx *tmlx, float ang, float ray_is_left)
{
	t_fpoint	v_inter;
	float		x_step;
	float		y_step;

	x_step = BOX_SIZE;
	y_step = BOX_SIZE * tan(ang);
	v_inter.x = floor(tmlx->tplyr->pos_px.x / BOX_SIZE) * BOX_SIZE;
	v_inter = ver_angl(ang, &ray_is_left, v_inter, &x_step);
	v_inter.y = tmlx->tplyr->pos_px.y + \
	(v_inter.x - tmlx->tplyr->pos_px.x) * tan(ang);
	if ((unit_circle(ang, 'x') && y_step < 0) || \
	(!unit_circle(ang, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(tmlx, v_inter.x - ray_is_left, v_inter.y))
	{
		v_inter.x += x_step;
		v_inter.y += y_step;
	}
	tmlx->tray->vertical.x = v_inter.x;
	tmlx->tray->vertical.y = v_inter.y;
	return (sqrt(pow(v_inter.x - tmlx->tplyr->pos_px.x, 2) + \
	pow(v_inter.y - tmlx->tplyr->pos_px.y, 2)));
}

float	get_dist_hor_w(t_mlx *tmlx, float ray_angl)
{
	t_fpoint	h_inter;
	float		x_step;
	float		y_step;

	y_step = BOX_SIZE;
	h_inter.y = floor(tmlx->tplyr->pos_px.y / BOX_SIZE) * BOX_SIZE;
	h_inter = hor_angl(ray_angl, h_inter, &y_step);
	h_inter.x = tmlx->tplyr->pos_px.x + \
	(h_inter.y - tmlx->tplyr->pos_px.y) / tan(ray_angl);
	x_step = BOX_SIZE / tan(ray_angl);
	if ((unit_circle(ray_angl, 'y') && x_step > 0) || \
	(!unit_circle(ray_angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(tmlx, h_inter.x, h_inter.y))
	{
		h_inter.x += x_step;
		h_inter.y += y_step;
	}
	tmlx->tray->horizontal.x = h_inter.x;
	tmlx->tray->horizontal.y = h_inter.y;
	return (sqrt(pow(h_inter.x - tmlx->tplyr->pos_px.x, 2) \
	+ pow(h_inter.y - tmlx->tplyr->pos_px.y, 2)));
}

void	cast_rays(t_mlx *tmlx)
{
	double	dist_hor_w;
	double	dist_ver_w;
	int		ray;

	ray = 0;
	tmlx->tray->ray_angl = tmlx->tplyr->view_dir - (tmlx->tplyr->fov_rad / 2);
	while (ray < tmlx->mlx->width)
	{
		dist_hor_w = get_dist_hor_w(tmlx, nor_angle(tmlx->tray->ray_angl));
		dist_ver_w = get_dist_ver_w(tmlx, nor_angle(tmlx->tray->ray_angl), 0);
		if (dist_ver_w <= dist_hor_w)
		{
			tmlx->tray->wall_dist = dist_ver_w;
			tmlx->tray->wall_f = 0;
		}
		else
		{
			tmlx->tray->wall_dist = dist_hor_w;
			tmlx->tray->wall_f = 1;
		}
		render(tmlx, ray);
		ray++;
		tmlx->tray->ray_angl += (tmlx->tplyr->fov_rad / S_WIDTH);
	}
}
