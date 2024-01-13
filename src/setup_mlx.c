/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:10:52 by pcheron           #+#    #+#             */
/*   Updated: 2024/01/13 13:40:07 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_values(t_data *data)
{
	data->camera_dir[0] = -1.0;
	data->camera_dir[1] = 0.0;
	data->controls.w = false;
	data->controls.s = false;
	data->controls.a = false;
	data->controls.d = false;
}

int	data_clear(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_image(data->mlx, data->north.img);
	mlx_destroy_image(data->mlx, data->south.img);
	mlx_destroy_image(data->mlx, data->east.img);
	mlx_destroy_image(data->mlx, data->west.img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_strs(&data->map);
	exit(0);
	return (0);
}

bool	setup_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (write(2, "mlx : error mlx init\n", 15), false);
	data->win = mlx_new_window(data->mlx, IMG_WIDTH, IMG_HEIGHT, "cub3D");
	if (!data->win)
		return (write(2, "mlx : error mlx new window\n", 15),
			mlx_destroy_image(data->mlx, data->img.img),
			mlx_destroy_display(data->mlx), free(data->mlx), false);
	data->img.img = mlx_new_image(data->mlx, IMG_WIDTH, IMG_HEIGHT);
	if (!data->img.img)
		return (write(2, "mlx : error mlx new img\n", 15),
			mlx_destroy_display(data->mlx), free(data->mlx), false);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.ll, &data->img.endian);
	if (!data->img.addr)
		return (write(2, "mlx : error mlx get addr\n", 15),
			mlx_destroy_image(data->mlx, data->img.img),
			mlx_destroy_display(data->mlx), free(data->mlx), false);
	data->img.bpp /= 8;
	return (true);
}
