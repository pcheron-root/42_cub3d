/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 13:53:37 by pcheron           #+#    #+#             */
/*   Updated: 2024/01/06 17:54:34 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	int color;
	int	tex_y;

	while (*i <= end && *i < IMG_HEIGHT)
	{
		tex_y = (int)data->tex_pos & (TEX_HEIGHT - 1);
		data->tex_pos += data->step_all;
		if (data->side == NORTH)
			color = ((int *)data->north.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		else if (data->side == SOUTH)
			color = ((int *)data->south.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		else if (data->side == WEST)
			color = ((int *)data->west.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		else
			color = ((int *)data->east.addr)[tex_y * TEX_HEIGHT + data->tex_x];
		
		// pour assombrir certains murs
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
		else
		{
			
		}
	}
}

void	draw_slice(t_data *data, int x, int start, int end)
{
	int	i;

	i = 0;
	draw_floor(data, x, start, &i);
	draw_wall(data, x, end, &i);
	draw_ceiling(data, x, &i);
}
