/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:35:00 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/25 19:35:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <sys/types.h>

int	color_to_int_no_alpha(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
}

int	color_to_int_alpha(t_color color, uint8_t opacity)
{
	return ((opacity << 24) | (color.b << 16) | (color.g << 8) | color.r);
}

t_color	color_scale(t_color c, double factor)
{
	int		rgb[3];

	rgb[0] = (int)((double)c.r * factor);
	rgb[1] = (int)((double)c.g * factor);
	rgb[2] = (int)((double)c.b * factor);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	if (rgb[0] < 0)
		rgb[0] = 0;
	if (rgb[1] < 0)
		rgb[1] = 0;
	if (rgb[2] < 0)
		rgb[2] = 0;
	return ((t_color){rgb[0], rgb[1], rgb[2]});
}
