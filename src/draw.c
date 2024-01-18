/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:53:37 by pcheron           #+#    #+#             */
/*   Updated: 2024/01/18 14:53:27 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_my_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (x * IMG_WIDTH * 4 + y * 4);
	*(unsigned int *)dst = color;
}

// effet de ouf drogueee
// void	ft_my_put_pixel(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->img.addr + (x * IMG_WIDTH * 4 + y * 4);
// 	*(unsigned int *)dst = color;
// }

void	draw_floor(t_data *data, int x, int start, int *i)
{
	int	color;

	while (*i <= start && *i < IMG_HEIGHT)
	{
		if (!data->floor.img)
		{
			color = data->floor_color[0];
			color <<= 8;
			color += data->floor_color[1];
			color <<= 8;
			color += data->floor_color[2];
			ft_my_put_pixel(data, *i, x, color);
			(*i)++;
		}
	}
}

void	draw_wall(t_data *data, int x, int end, int *i)
{
	int	color;
	int	tex_y;

	data->tex_pos_tmp = data->tex_pos;
	while (*i <= end && *i < IMG_HEIGHT)
	{
		tex_y = (int)data->tex_pos & (TEX_HEIGHT - 1);
		data->tex_pos += data->step_all;
		if (data->display_door)
		{
			color = ((int *)data->door.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		}
		else if (data->side == SOUTH)
			color = ((int *)data->north.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		else if (data->side == NORTH)
			color = ((int *)data->south.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		else if (data->side == EAST)
			color = ((int *)data->west.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		else
			color = ((int *)data->east.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		if (data->side - 2)
			color = (color >> 1) & 8355711;
		ft_my_put_pixel(data, *i, x, color);
		(*i)++;
	}
}

void	draw_ceiling(t_data *data, int x, int *i)
{
	int	color;

	while (*i < IMG_HEIGHT)
	{
		if (!data->ceiling.img)
		{
			color = data->ceiling_color[0];
			color <<= 8;
			color += data->ceiling_color[1];
			color <<= 8;
			color += data->ceiling_color[2];
			ft_my_put_pixel(data, *i, x, color);
			(*i)++;
		}
	}
}

void	draw_catterpilar(t_data *data, int x, int end, int i)
{
	int	color;
	int	tex_y;

	while (i <= end && i < IMG_HEIGHT)
	{
		tex_y = (int)data->tex_pos_tmp & (128 - 1);
		data->tex_pos_tmp += data->step_all;
		color = ((int *)data->catterpilar[data->time/200].addr)[tex_y * 128 + data->tex_x];
		if (color > 0)
			ft_my_put_pixel(data, i, x, color);
		(i)++;
	}
}

void	draw_slice(t_data *data, int x)
{
	int	i;
	int	tmp;

	i = 0;
	draw_floor(data, x, data->draw_start, &i);
	tmp = i;
	draw_wall(data, x, data->draw_end, &i);
	if (data->display_catterpilar)
		draw_catterpilar(data, x, data->draw_end, tmp);
	draw_ceiling(data, x, &i);
}
