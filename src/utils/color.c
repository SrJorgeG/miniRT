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
	
	color_split = ft_split(color_str, ',');
	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->r = ft_atoi(color_split[0]);	
	color->g = ft_atoi(color_split[1]);	
	color->b = ft_atoi(color_split[2]);
	if (color->r > 255 && color->g > 255 && color->b > 255)
		return (free(color), NULL);
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
        if (ft_isdigit(*str) && ((digit_len == 0 && *str <= '2')
			|| (digit_len == 1 && *str <= '5')
			|| (digit_len == 2 && *str <= '5')))
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