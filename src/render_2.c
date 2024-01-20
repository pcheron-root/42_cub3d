/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:44:49 by pcheron           #+#    #+#             */
/*   Updated: 2024/01/20 11:27:20 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	door_behavior(t_data *data)
// {
// 	if (data->map[data->map_x][data->map_y] == 'D')
// 		data->side = DOOR;
// 	// else
// 	// 	data->display_door = false;
// }

static bool	side_assignment(t_data *data, t_v2f delta_dist)
{
	if (data->side_dist[0] < data->side_dist[1])
	{
		data->side_dist[0] += delta_dist[0];
		data->map_x += data->step[0];
		data->side = 2 - (data->map_x > data->player_pos[0]);
		// if (data->map_x > data->player_pos[0])
		// 	data->side = NORTH;
		// else
		// 	data->side = SOUTH;
	}
	else
	{
		data->side_dist[1] += delta_dist[1];
		data->map_y += data->step[1];
		data->side = EAST - (data->map_y > data->player_pos[1]);
		// if (data->map_y > data->player_pos[1])
		// 	data->side = WEST;
		// else
		// 	data->side = EAST;
	}
	if (data->map[data->map_x][data->map_y] == 'D')
		return (data->side = DOOR, true);
	if (data->map[data->map_x][data->map_y] == '1')
	{
		if (data->map_x == 0 && data->map_y == 10)
			data->display_catterpilar = true;
		else
			data->display_catterpilar = false;
		return (true);
	}
	return (false);
}

static void	side_calc(t_data *data, t_v2f ray, t_v2f delta_dist)
{
	if (ray[0] < 0)
	{
		data->step[0] = -1;
		data->side_dist[0] = (data->player_pos[0] - data->map_x) \
		* delta_dist[0];
	}
	else
	{
		data->step[0] = 1;
		data->side_dist[0] = (data->map_x + 1.0 - data->player_pos[0]) \
		* delta_dist[0];
	}
	if (ray[1] < 0)
	{
		data->step[1] = -1;
		data->side_dist[1] = (data->player_pos[1] - data->map_y) * \
		delta_dist[1];
	}
	else
	{
		data->step[1] = 1;
		data->side_dist[1] = (data->map_y + 1.0 - data->player_pos[1]) * \
		delta_dist[1];
	}
}

void	next_cube(t_data *data, t_v2f ray, int x, t_v2f delta_dist)
{
	side_calc(data, ray, delta_dist);
	while (!side_assignment(data, delta_dist))
		;
	wall_calc(data, ray, data->side_dist[data->side / 3] \
	- delta_dist[data->side / 3]);
	draw_slice(data, x);
}
