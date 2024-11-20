/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:11:44 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/20 16:47:49 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* Check the ray angle to know if it's left or right and fix values */
t_fpoint	ver_angl(float a, float *ray_islft, t_fpoint v_itr, float *x_stp)
{
	if (a > M_PI / 2 && a < 3 * M_PI / 2)
	{
		*x_stp *= -1;
		*ray_islft = 1;
	}
	else
		v_itr.x += BOX_SIZE;
	return (v_itr);
}

/* Check the ray angle to know if it's up or down and fix values */
t_fpoint	hor_angl(float a, float *ray_isdwn, t_fpoint h_itr, float *y_stp)
{
	if (a > 0 && a < M_PI)
		h_itr.y += BOX_SIZE;
	else
	{
		*ray_isdwn = 1;
		*y_stp *= -1;
	}
	return (h_itr);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}
