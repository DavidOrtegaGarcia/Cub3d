#include "cub.h"


void	move(t_mlx *tmlx, t_dpoint mov)
{
	int		map_box_x;
	int		map_box_y;
	int		new_x;
	int		new_y;

	new_x = roundf(tmlx->tplyr->pos_px.x + mov.x);
	new_y = roundf(tmlx->tplyr->pos_px.y + mov.y);
	map_box_x = (new_x / BOX_SIZE);
	map_box_y = (new_y / BOX_SIZE);
	if (tmlx->tmap.content[map_box_y][map_box_x] != '1' &&
	(tmlx->tmap.content[map_box_y][tmlx->tplyr->pos_px.x / BOX_SIZE] != '1' &&
	tmlx->tmap.content[tmlx->tplyr->pos_px.y / BOX_SIZE][map_box_x] != '1'))
	{
		tmlx->tplyr->pos_px.x = new_x;
		tmlx->tplyr->pos_px.y = new_y;
	}
}

void	rotate(t_mlx *tmlx, int dir)
{
	if (dir == 1) // TURN RIGTH
	{
		tmlx->tplyr->view_dir += ROTATION_SPD;
		if (tmlx->tplyr->view_dir > 2 * M_PI) // If the player rotate 360 degrers we ajust the value to stay in the correct range
			tmlx->tplyr->view_dir -= 2 * M_PI;
	}
	else // TURN LEFT
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
	if (tmlx->tplyr->up_dwn_f == 1) // MOVE UP
	{
		mov.x = cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	if (tmlx->tplyr->up_dwn_f == -1) // MOVE DOWN
	{
		mov.x = -cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = -sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	if (tmlx->tplyr->lft_rhg_f == 1) // MOVE RIGHT
	{
		mov.x = -sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	if (tmlx->tplyr->lft_rhg_f == -1) // MOVE LEFT
	{
		mov.x = sin(tmlx->tplyr->view_dir) * PLAYER_SPD;
		mov.y = -cos(tmlx->tplyr->view_dir) * PLAYER_SPD;
	}
	move(tmlx, mov);
}

void	release_key(mlx_key_data_t data_key, t_mlx *tmlx)
{
	if ((data_key.key == MLX_KEY_W && data_key.action == MLX_RELEASE) ||
		(data_key.key == MLX_KEY_S && data_key.action == MLX_RELEASE))
		tmlx->tplyr->up_dwn_f = 0;
	else if ((data_key.key == MLX_KEY_A && data_key.action == MLX_RELEASE) ||
		(data_key.key == MLX_KEY_D && data_key.action == MLX_RELEASE))
		tmlx->tplyr->lft_rhg_f = 0;
	else if ((data_key.key == MLX_KEY_LEFT && data_key.action == MLX_RELEASE) ||
		(data_key.key == MLX_KEY_RIGHT && data_key.action == MLX_RELEASE))
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
