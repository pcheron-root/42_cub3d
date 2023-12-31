/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 10:59:01 by pcheron           #+#    #+#             */
/*   Updated: 2024/01/06 18:32:10 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_handle_key_arrow(int key, t_data *data)
{
	//printf("key : %d\n", key);
	// printf("MOVE_SPEED : %f\n", MOVE_SPEED);
	if (key == UP || key == UP_W)
	{
		data->controls.w = true;
		// data->player_pos[0] -= 1.0;	
			// if (data->map[(int)(data->player_pos[0] + data->camera_dir[0] * (float)MOVE_SPEED)][(int)data->player_pos[1]] != '1')
			// 	data->player_pos[0] += data->camera_dir[0] * (float)MOVE_SPEED;
			// if (data->map[(int)data->player_pos[0]][(int)(data->player_pos[1] + data->camera_dir[1] * (float)MOVE_SPEED)] != '1')
			// 	data->player_pos[1] += data->camera_dir[1] * (float)MOVE_SPEED;
	}
	else if (key == DOWN || key == DOWN_S)
	{
		data->controls.s = true;
		// if (data->map[(int)(data->player_pos[0] - data->camera_dir[0] * (float)MOVE_SPEED)][(int)data->player_pos[1]] != '1')
		// 	data->player_pos[0] -= data->camera_dir[0] * (float)MOVE_SPEED;
		// if (data->map[(int)data->player_pos[0]][(int)(data->player_pos[1] - data->camera_dir[1] * (float)MOVE_SPEED)] != '1')
		// 	data->player_pos[1] -= data->camera_dir[1] * (float)MOVE_SPEED;
	}
	// t_v2f	old_dir = data->camera_dir;
	// t_v2f	old_plane;
	if (key == RIGHT || key == RIGHT_D)
	{
		data->controls.d = true;
		// data->camera_dir[0] = data->camera_dir[0] * cos(-ROT_SPEED) - data->camera_dir[1] * sin(-ROT_SPEED);
		// data->camera_dir[1] = old_dir[0] * sin(-ROT_SPEED) + data->camera_dir[1] * cos(-ROT_SPEED);
		// old_plane[0] = data->plane[0];
		// data->plane[0] = data->plane[0] * cos(-ROT_SPEED) - data->plane[1] * sin(-ROT_SPEED);
		// data->plane[1] = old_plane[0] * sin(-ROT_SPEED) + data->plane[1] * cos(-ROT_SPEED);

	}
	else if (key == LEFT || key == LEFT_A)
	{
		data->controls.a = true;
		// data->camera_dir[0] = data->camera_dir[0] * cos(ROT_SPEED) - data->camera_dir[1] * sin(ROT_SPEED);
		// data->camera_dir[1] = old_dir[0] * sin(ROT_SPEED) + data->camera_dir[1] * cos(ROT_SPEED);
		// old_plane[0] = data->plane[0];
		// data->plane[0] = data->plane[0] * cos(ROT_SPEED) - data->plane[1] * sin(ROT_SPEED);
		// data->plane[1] = old_plane[0] * sin(ROT_SPEED) + data->plane[1] * cos(ROT_SPEED);
	}
	// printf("player / camera\n");
	// put_v2f(data->player_pos);
	// put_v2f(data->camera_dir);
	// render(data);
}

void	move(t_data *data)
{
	if (data->controls.w)
	{
		if (data->map[(int)(data->player_pos[0] + data->camera_dir[0] * (float)MOVE_SPEED)][(int)data->player_pos[1]] != '1')
			data->player_pos[0] += data->camera_dir[0] * (float)MOVE_SPEED;
		if (data->map[(int)data->player_pos[0]][(int)(data->player_pos[1] + data->camera_dir[1] * (float)MOVE_SPEED)] != '1')
			data->player_pos[1] += data->camera_dir[1] * (float)MOVE_SPEED;
	}
	else if (data->controls.s)
	{
		if (data->map[(int)(data->player_pos[0] - data->camera_dir[0] * (float)MOVE_SPEED)][(int)data->player_pos[1]] != '1')
			data->player_pos[0] -= data->camera_dir[0] * (float)MOVE_SPEED;
		if (data->map[(int)data->player_pos[0]][(int)(data->player_pos[1] - data->camera_dir[1] * (float)MOVE_SPEED)] != '1')
			data->player_pos[1] -= data->camera_dir[1] * (float)MOVE_SPEED;
	}
	t_v2f	old_dir = data->camera_dir;
	t_v2f	old_plane;
	if (data->controls.d)
	{
		data->camera_dir[0] = data->camera_dir[0] * cos(-ROT_SPEED) - data->camera_dir[1] * sin(-ROT_SPEED);
		data->camera_dir[1] = old_dir[0] * sin(-ROT_SPEED) + data->camera_dir[1] * cos(-ROT_SPEED);
		old_plane[0] = data->plane[0];
		data->plane[0] = data->plane[0] * cos(-ROT_SPEED) - data->plane[1] * sin(-ROT_SPEED);
		data->plane[1] = old_plane[0] * sin(-ROT_SPEED) + data->plane[1] * cos(-ROT_SPEED);

	}
	else if (data->controls.a)
	{
		data->camera_dir[0] = data->camera_dir[0] * cos(ROT_SPEED) - data->camera_dir[1] * sin(ROT_SPEED);
		data->camera_dir[1] = old_dir[0] * sin(ROT_SPEED) + data->camera_dir[1] * cos(ROT_SPEED);
		old_plane[0] = data->plane[0];
		data->plane[0] = data->plane[0] * cos(ROT_SPEED) - data->plane[1] * sin(ROT_SPEED);
		data->plane[1] = old_plane[0] * sin(ROT_SPEED) + data->plane[1] * cos(ROT_SPEED);
	}
	render(data);
}

int	key_release(int key, t_data *data)
{
	if (key == UP || key == UP_W)
		data->controls.w = false;
	else if (key == DOWN || key == DOWN_S)
		data->controls.s = false;
	else if (key == LEFT || key == LEFT_A)
		data->controls.a = false;
	else if (key == RIGHT || key == RIGHT_D)
		data->controls.d = false;
	return (0);
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		return (data_clear(data), 0);
	ft_handle_key_arrow(keycode, data);
	return (0);
}

void	ft_my_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (x * IMG_HEIGHT * 4 + y * 4);
	*(unsigned int *)dst = color;
}

//Fonction plus utilisee
// void	put_col(t_data *data, int col, int start, int end, int color)
// {
// 	int	i;

// 	i = 0;
// 	while (i < start && i < IMG_WIDTH)
// 	{
// 		ft_my_put_pixel(data, i, col, 0x00223240);
// 		i++;
// 	}
// 	while (start <= end)
// 	{
// 		ft_my_put_pixel(data, start, col, color);
// 		start++;
// 	}
// 	while (start < IMG_HEIGHT)
// 	{
// 		ft_my_put_pixel(data, start, col, 0x00353535);
// 		start++;
// 	}
// }
