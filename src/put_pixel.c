/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:44:16 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/19 21:44:23 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return (1);
	mlx_put_pixel(img, x, y, color);
	return (0);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
