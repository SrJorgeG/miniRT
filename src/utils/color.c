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
#include <sys/types.h>

u_int8_t	create_color(char *color_str, t_color *color)
{
	char	**color_split;
	long			rgb[3];

	color_split = ft_split(color_str, ',');
	rgb[0] = ft_atol(color_split[0]);
	rgb[1] = ft_atol(color_split[1]);
	rgb[2] = ft_atol(color_split[2]);
	ft_free_split(color_split);
	if ((rgb[0] > 255 || rgb[0] < 0) && (rgb[1] > 255 || rgb[1] < 0) && (rgb[2] > 255 || rgb[2] < 0))
		return (0);
	color->r = (unsigned char)rgb[0];
	color->g = (unsigned char)rgb[1];
	color->b = (unsigned char)rgb[2];
	return (1);
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


// Multiplica dos colores componente a componente normalizando a [0,1], y multiplicando vuelve a [0,255]
t_color color_multiply(t_color c1, t_color c2)
{
    t_color result;
	int rgb[3];

    rgb[0] = (int)(((double)c1.r / 255.0) * ((double)c2.r / 255.0) * 255.0);
    rgb[1] = (int)(((double)c1.g / 255.0) * ((double)c2.g / 255.0) * 255.0);
    rgb[2] = (int)(((double)c1.b / 255.0) * ((double)c2.b / 255.0) * 255.0);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	result.r = rgb[0];
	result.g = rgb[1];
	result.b = rgb[2];
    return result;
}

// Multiplica un color por un numero
t_color color_scale(t_color c, double factor)
{
    t_color result;
	int rgb[3];

    rgb[0] = (int)((double)c.r * factor);
    rgb[1] = (int)((double)c.g * factor);
    rgb[2] = (int)((double)c.b * factor);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	result.r = rgb[0];
	result.g = rgb[1];
	result.b = rgb[2];
    return result;
}

// Suma dos colores
t_color color_add(t_color c1, t_color c2)
{
    t_color result;
	int rgb[3];

    rgb[0] = c1.r + c2.r;
    rgb[1] = c1.g + c2.g;
    rgb[2] = c1.b + c2.b;
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	result.r = rgb[0];
	result.g = rgb[1];
	result.b = rgb[2];
    return result;
}

// Se asegura de que los valores del color no superen 255
void color_clamp(int c[3])
{
	if (c[0] < 0)
		c[0] = 0;
    if (c[1] < 0)
		c[1] = 0;
    if (c[2] < 0)
		c[2] = 0;
    if (c[0] > 255)
		c[0] = 255;
    if (c[1] > 255)
		c[1] = 255;
    if (c[2] > 255)
		c[2] = 255;
}

// Asumo que tienes un struct t_scene que contiene los punteros a la luz ambiental y la lista de luces

//int color_to_int_alpha(t_color color)
//{
//    // Empaqueta los bytes en el orden R, G, B, A
//   // return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
//}
int color_to_int_no_alpha(t_color color)
{
    // Asume que el canal Alfa es 255 (totalmente opaco)
    return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
}
