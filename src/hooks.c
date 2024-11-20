/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiro-co <emiro-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:49:03 by emiro-co          #+#    #+#             */
/*   Updated: 2024/11/20 19:08:26 by emiro-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move(t_mlx *tmlx, t_dpoint mov)
{
	t_point	new_pos;
	int		left_margin_x;
	int		right_margin_x;
	int		top_margin_y;
	int		bottom_margin_y;

	new_pos.x = (int)roundf(tmlx->tplyr->pos_px.x + mov.x);
	new_pos.y = (int)roundf(tmlx->tplyr->pos_px.y + mov.y);
	left_margin_x = (new_pos.x - COLLISION_MARGIN) / BOX_SIZE;
	right_margin_x = (new_pos.x + COLLISION_MARGIN) / BOX_SIZE;
	top_margin_y = (new_pos.y - COLLISION_MARGIN) / BOX_SIZE;
	bottom_margin_y = (new_pos.y + COLLISION_MARGIN) / BOX_SIZE;
	if (tmlx->tmap.content[top_margin_y][left_margin_x] != '1' &&
		tmlx->tmap.content[top_margin_y][right_margin_x] != '1' &&
		tmlx->tmap.content[bottom_margin_y][left_margin_x] != '1' &&
		tmlx->tmap.content[bottom_margin_y][right_margin_x] != '1')
	{
		tmlx->tplyr->pos_px.x = new_pos.x;
		tmlx->tplyr->pos_px.y = new_pos.y;
	}
}

void	rotate(t_mlx *tmlx, int dir)
{
	if (dir == 1)
	{
		tmlx->tplyr->view_dir += ROTATION_SPD;
		if (tmlx->tplyr->view_dir > 2 * M_PI)
			tmlx->tplyr->view_dir -= 2 * M_PI;
	}
	else
	{
		tmlx->tplyr->view_dir -= ROTATION_SPD;
		if (tmlx->tplyr->view_dir < 0)
			tmlx->tplyr->view_dir += 2 * M_PI;
	}
}

void	movment_hook(t_mlx *tmlx, t_dpoint mov)
{
	if (tmlx->tplyr->rot_f == 1)
		rotate(tmlx, 1);
	if (tmlx->tplyr->rot_f == -1)
		rotate(tmlx, -1);
	if (tmlx->tplyr->up_dwn_f == 1)
	{
		mov.x = cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	if (tmlx->tplyr->up_dwn_f == -1)
	{
		mov.x = -cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = -sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	if (tmlx->tplyr->lft_rhg_f == 1)
	{
		mov.x = -sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	if (tmlx->tplyr->lft_rhg_f == -1)
	{
		mov.x = sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = -cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	move(tmlx, mov);
}

void	release_key(mlx_key_data_t data_key, t_mlx *tmlx)
{
	if ((data_key.key == MLX_KEY_W && data_key.action == MLX_RELEASE) \
	|| (data_key.key == MLX_KEY_S && data_key.action == MLX_RELEASE))
		tmlx->tplyr->up_dwn_f = 0;
	else if ((data_key.key == MLX_KEY_A && data_key.action == MLX_RELEASE) \
	|| (data_key.key == MLX_KEY_D && data_key.action == MLX_RELEASE))
		tmlx->tplyr->lft_rhg_f = 0;
	else if ((data_key.key == MLX_KEY_LEFT && data_key.action == MLX_RELEASE) \
	|| (data_key.key == MLX_KEY_RIGHT && data_key.action == MLX_RELEASE))
		tmlx->tplyr->rot_f = 0;
}

void	key_hook(mlx_key_data_t data_key, void *param)
{
	t_mlx	*tmlx;

	tmlx = param;
	if (data_key.key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	else if (data_key.key == MLX_KEY_W && data_key.action == MLX_PRESS)
		tmlx->tplyr->up_dwn_f = 1;
	else if (data_key.key == MLX_KEY_S && data_key.action == MLX_PRESS)
		tmlx->tplyr->up_dwn_f = -1;
	else if (data_key.key == MLX_KEY_A && data_key.action == MLX_PRESS)
		tmlx->tplyr->lft_rhg_f = -1;
	else if (data_key.key == MLX_KEY_D && data_key.action == MLX_PRESS)
		tmlx->tplyr->lft_rhg_f = 1;
	else if (data_key.key == MLX_KEY_LEFT && data_key.action == MLX_PRESS)
		tmlx->tplyr->rot_f = -1;
	else if (data_key.key == MLX_KEY_RIGHT && data_key.action == MLX_PRESS)
		tmlx->tplyr->rot_f = 1;
	release_key(data_key, tmlx);
}
