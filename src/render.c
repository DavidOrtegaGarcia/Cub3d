/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:46 by afatir            #+#    #+#             */
/*   Updated: 2024/11/20 10:47:56 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_flr_cling(t_mlx *tmlx, int ray, int top_wpixel, int bot_wpixel)
{
	int	i;
	int	color;

	color = get_rgba(tmlx->tmap.celling.r, \
	tmlx->tmap.celling.g, tmlx->tmap.celling.b, 255);
	i = 0;
	while (i < top_wpixel)
	{
		my_put_pixel(tmlx->img, ray, i, color);
		i++;
	}
	i = bot_wpixel;
	color = get_rgba(tmlx->tmap.floor.r, \
	tmlx->tmap.floor.g, tmlx->tmap.floor.b, 255);
	while (i < tmlx->mlx->height)
	{
		my_put_pixel(tmlx->img, ray, i, color);
		i++;
	}
}

mlx_texture_t	*get_texture(t_mlx *tmlx, int wall_f)
{
	tmlx->tray->ray_angl = nor_angle(tmlx->tray->ray_angl);
	if (wall_f == 0)
	{
		if (tmlx->tray->ray_angl > M_PI / 2 && \
		tmlx->tray->ray_angl < 3 * (M_PI / 2))
			return (tmlx->tmap.east);
		else
			return (tmlx->tmap.west);
	}
	else
	{
		if (tmlx->tray->ray_angl > 0 && tmlx->tray->ray_angl < M_PI)
			return (tmlx->tmap.south);
		else
			return (tmlx->tmap.north);
	}
}

double	get_texture_x(mlx_texture_t	*texture, t_mlx *tmlx)
{
	double	texture_x;

	if (tmlx->tray->wall_f == 1)
		texture_x = fmod((tmlx->tray->horizontal.x / BOX_SIZE) \
		* texture->width, texture->width);
	else
		texture_x = fmod((tmlx->tray->vertical.y / BOX_SIZE) \
		* texture->width, texture->width);
	if (texture_x < 0)
		texture_x += texture->width;
	if (texture_x >= texture->width)
		texture_x -= texture->width;
	return (texture_x);
}

void	print_wall(t_mlx *tmlx, int top_wpixel, int bot_wpixel, double wall_h)
{
	mlx_texture_t	*texture;
	uint32_t		*tex_pixels;
	double			scaling_f;
	t_dpoint		tex_point;

	texture = get_texture(tmlx, tmlx->tray->wall_f);
	if (!texture || !texture->pixels)
		return ;
	tex_pixels = (uint32_t *)texture->pixels;
	scaling_f = (double)texture->height / wall_h;
	tex_point.x = get_texture_x(texture, tmlx);
	if (tex_point.x < 0 || tex_point.x >= (int)texture->width)
		return ;
	tex_point.y = (top_wpixel - (S_HEIGHT / 2) + (wall_h / 2)) * scaling_f;
	if (tex_point.y < 0)
		tex_point.y = 0;
	while (top_wpixel < bot_wpixel)
	{
		if ((int)tex_point.y >= (int)texture->height)
			break ;
		my_put_pixel(tmlx->img, tmlx->tray->ray_num, top_wpixel, reverse_bytes(\
		tex_pixels[(int)tex_point.y * texture->width + (int)tex_point.x]));
		tex_point.y += scaling_f;
		top_wpixel++;
	}
}

void	render(t_mlx *tmlx, int ray)
{
	double	wall_height;
	double	top_wpixel;
	double	bot_wpixel;

	tmlx->tray->wall_dist *= cos(nor_angle(tmlx->tray->ray_angl \
	- tmlx->tplyr->view_dir));
	wall_height = (BOX_SIZE / tmlx->tray->wall_dist) * \
	((S_WIDTH / 2) / tan(tmlx->tplyr->fov_rad / 2));
	top_wpixel = (S_HEIGHT / 2) - (wall_height / 2);
	bot_wpixel = (S_HEIGHT / 2) + (wall_height / 2);
	if (top_wpixel < 0)
		top_wpixel = 0;
	if (bot_wpixel > S_HEIGHT)
		bot_wpixel = S_HEIGHT;
	tmlx->tray->ray_num = ray;
	print_wall(tmlx, top_wpixel, bot_wpixel, wall_height);
	print_flr_cling(tmlx, ray, top_wpixel, bot_wpixel);
}
