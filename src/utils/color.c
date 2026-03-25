/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:49 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <sys/types.h>

u_int8_t	create_color(char *color_str, t_color *color)
{
	char	**split;
	long	rgb[3];

	split = ft_split(color_str, ',');
	rgb[0] = ft_atol(split[0]);
	rgb[1] = ft_atol(split[1]);
	rgb[2] = ft_atol(split[2]);
	ft_free_split(split);
	if ((rgb[0] > 255 || rgb[0] < 0) && (rgb[1] > 255 || rgb[1] < 0)
		&& (rgb[2] > 255 || rgb[2] < 0))
		return (0);
	color->r = (unsigned char)rgb[0];
	color->g = (unsigned char)rgb[1];
	color->b = (unsigned char)rgb[2];
	return (1);
}

int	ft_str_is_color(char *str)
{
	int	comp;
	int	dlen;

	comp = 0;
	dlen = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			if (dlen >= 3)
				return (0);
			dlen++;
		}
		else if (*str == ',' && dlen > 0 && comp < 2)
		{
			comp++;
			dlen = 0;
		}
		else
			return (0);
		str++;
	}
	return (comp == 2 && dlen > 0);
}

t_color	color_multiply(t_color c1, t_color c2)
{
	int		rgb[3];

	rgb[0] = (int)(((double)c1.r / 255.0) * ((double)c2.r / 255.0) * 255.0);
	rgb[1] = (int)(((double)c1.g / 255.0) * ((double)c2.g / 255.0) * 255.0);
	rgb[2] = (int)(((double)c1.b / 255.0) * ((double)c2.b / 255.0) * 255.0);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	return ((t_color){rgb[0], rgb[1], rgb[2]});
}

t_color	color_add(t_color c1, t_color c2)
{
	int		rgb[3];

	rgb[0] = c1.r + c2.r;
	rgb[1] = c1.g + c2.g;
	rgb[2] = c1.b + c2.b;
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	return ((t_color){rgb[0], rgb[1], rgb[2]});
}

int	color_to_int(t_color color, uint8_t opacity)
{
	return ((opacity << 24) | (color.b << 16) | (color.g << 8) | color.r);
}
