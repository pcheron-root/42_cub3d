/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kquerel <kquerel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 18:12:14 by kquerel           #+#    #+#             */
/*   Updated: 2024/01/18 19:58:42 by kquerel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	upload_img(t_data *data, t_img_info *img, char *file)
{
	img->img = mlx_xpm_file_to_image(data->mlx, file, \
	&img->width, &img->height);
	if (!img->img)
		return (false);
	img->addr = mlx_get_data_addr(img->img, \
	&img->bpp, &img->ll, &img->endian);
	if (!img->addr)
		return (false);
	return (true);
}

bool	get_alice(t_data *data)
{
	static char	file[17] = "img/Alice/xx.xpm\0";
	int			i;

	i = 1;
	while (i - 1 < 18)
	{
		file[10] = i / 10 + '0';
		file[11] = i % 10 + '0';
		if (!upload_img(data, &((data->alice)[i - 1]), file))
			return (err(strerror(errno)), false);
		i++;
	}
	return (true);
}
