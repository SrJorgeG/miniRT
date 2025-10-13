/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:49 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	*create_color(char *color_str)
{
	char	**color_split;
	t_color	*color;
	long			rgb[3];
	
	
	color = malloc(sizeof(t_color));
	if (!color)
		return (perror("malloc: "), NULL);
	color_split = ft_split(color_str, ',');
	rgb[0] = ft_atol(color_split[0]);	
	rgb[1] = ft_atol(color_split[1]);	
	rgb[2] = ft_atol(color_split[2]);
	ft_free_split(color_split);
	if ((rgb[0] > 255 || rgb[0] < 0) && (rgb[1] > 255 || rgb[1] < 0) && (rgb[2] > 255 || rgb[2] < 0))
		return (free(color),perror("color_range: "), NULL);
	color->r = (unsigned char)rgb[0];
	color->g = (unsigned char)rgb[1];
	color->b = (unsigned char)rgb[2];
	return (color);
}


int ft_str_is_color(char *str)
{
    int component_count = 0;
    int digit_len = 0;

    if (!str || *str == '\0')
        return (0);
    while (*str)
    {
        if (ft_isdigit(*str))
        {
            if (digit_len >= 3)
                return (0);
			digit_len++;
        }
        else if (*str == ',')
        {
            if (digit_len == 0 || component_count >= 2)
                return (0);
            component_count++;
            digit_len = 0;
        }
        else
            return (0);
        str++;
    }
    if (component_count == 2 && digit_len > 0)
        return (1);
    return (0);
}