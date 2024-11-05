/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:50:30 by daortega          #+#    #+#             */
/*   Updated: 2024/11/05 18:43:56 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

float get_h_inter(t_mlx *mlx, float angl) // get the horizontal intersection
{
	float h_x;
	float h_y;
	float x_step;
	float y_step;
	int  pixel;

	y_step = BOX_SIZE;
	x_step = BOX_SIZE / tan(angl);
	h_y = floor(mlx->tplyr->ply_p_px.y / BOX_SIZE) * BOX_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->tplyr->ply_p_px.x + (h_y - mlx->tplyr->ply_p_px.y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - mlx->tplyr->ply_p_px.x, 2) + pow(h_y - mlx->tplyr->ply_p_px.y, 2))); // get the distance
}

void cast_rays(t_mlx *tmlx) // cast the rays
{
	double interc_hor;
	double interc_ver;
	int  ray;

	ray = 0;
	tmlx->tray->ray_angl = tmlx->tplyr->view_dir - (tmlx->tplyr->fov_rad / 2); // the start angle
	while (ray < tmlx->mlx->width)
	{
		tmlx->tray->wall_f = 0; // flag for the wall
		interc_hor = get_h_inter(tmlx, nor_angle(tmlx->tray->ray_angl)); // get the horizontal intersection
		interc_ver = get_v_inter(tmlx, nor_angle(tmlx->tray->ray_angl)); // get the vertical intersection
		if (interc_ver <= interc_hor) // check the distance
			tmlx->tray->wall_dist = interc_ver; // get the distance
		else
		{
			tmlx->tray->wall_dist = interc_hor; // get the distance
			tmlx->tray->wall_f = 1; 
		}
		render_wall(tmlx, ray);
		ray++;
		tmlx->tray->ray_angl += (tmlx->tplyr->fov_rad / tmlx->mlx->width); // next angle
	}
}
