/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daortega <daortega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:50:30 by daortega          #+#    #+#             */
/*   Updated: 2024/10/29 18:52:44 by daortega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "cub.h"

void cast_rays(t_mlx *tmlx) // cast the rays
{
	double h_inter;
	double v_inter;
	int  ray;

	ray = 0;
	tmlx->tray->ray_angl = tmlx->tplayer->angle - (tmlx->tplayer->fov_rad / 2); // the start angle
	while (ray < tmlx->mlx->width) // loop for the rays
	{
		mlx->ray->flag = 0; // flag for the wall
		h_inter = get_h_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(mlx, nor_angle(mlx->ray->ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			mlx->ray->distance = v_inter; // get the distance
		else
		{
			mlx->ray->distance = h_inter; // get the distance
			mlx->ray->flag = 1; // flag for the wall
		}
		render_wall(mlx, ray); // render the wall
		ray++; // next ray
		mlx->ray->ray_ngl += (mlx->ply->fov_rd / S_W); // next angle
	}
}