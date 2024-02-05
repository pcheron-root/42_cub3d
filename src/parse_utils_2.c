/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:48:21 by pcheron           #+#    #+#             */
/*   Updated: 2024/01/26 09:45:44 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	jump_int(char **str)
{
	while (is_a_white_space(**str))
		(*str)++;
	while (**str >= '0' && **str <= '9')
		(*str)++;
}

bool	is_alpha(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	atocolor_continued(char *str, t_color *color, int color_tmp, char *tmp)
{
	if (!is_alpha(*str) && *str != '+' && *str != '-')
		return (false);
	ft_atoi(&color_tmp, str);
	while (is_alpha(*str) || *str == '+' || *str == '-')
		str++;
	(*color)[2] = color_tmp;
	if ((*color)[0] < 0 || (*color)[0] > 255 || (*color)[1] < 0 || \
		(*color)[1] > 255 || (*color)[2] < 0 || (*color)[2] > 255 || *str)
		return (false);
	str = tmp;
	return (true);
}

bool	atocolor(char *str, t_color *color)
{
	char	*tmp;
	int		color_tmp;

	tmp = str;
	while (is_a_white_space(*str))
		(*str)++;
	if (!is_alpha(*str) && *str != '+' && *str != '-')
		return (false);
	(ft_atoi(&color_tmp, str), jump_int(&str));
	(*color)[0] = color_tmp;
	if (*str == ',')
		str++;
	else
		return (false);
	if (!is_alpha(*str) && *str != '+' && *str != '-')
		return (false);
	(ft_atoi(&color_tmp, str), jump_int(&str));
	(*color)[1] = color_tmp;
	if (*str == ',')
		str++;
	else
		return (false);
	if (!atocolor_continued(str, color, color_tmp, tmp))
		return (false);
	return (true);
}

int	count_char_in_str(char c, char *str)
{
	int	count;

	count = 0;
	if (str)
	{
		while (*str)
		{
			if (c == *str)
				count++;
			str++;
		}
	}
	return (count);
}