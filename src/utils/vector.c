/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/13 15:45:48 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector	*create_vector(char *vector_str)
{
	char	**vector_split;
	t_vector	*vector;
	
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector_split = ft_split(vector_str, ',');
	vector->x = ft_atoi(vector_split[0]);	
	vector->y = ft_atoi(vector_split[1]);	
	vector->z = ft_atoi(vector_split[2]);
	ft_free_split(vector_split);
	if (vector->x > 255 && vector->y > 255 && vector->z > 255)
		return (free(vector), NULL);
	return (vector);
}

int ft_str_is_vector(char *str)
{
    int component_count = 0;
    int digit_len = 0;

    if (!str || *str == '\0')
        return (0);
    while (*str)
    {
        if (ft_isdigit(*str))
			digit_len++;
        else if (*str == ',')
        {
            if (digit_len == 0 || component_count >= 2)
                return (0);
            component_count++;
            digit_len = 0;
        }
        else if (*str != '-' && *str != '+' && *str != '.')
            return (0);
        str++;
    }
    if (component_count == 2 && digit_len > 0)
        return (1);
    return (0);
}

int is_normalized_vec(t_vector *vector)
{
	if (vector->x < -1 || vector->x > 1)
		return (0);
	if (vector->y < -1 || vector->y > 1)
		return (0);
	if (vector->z < -1 || vector->z > 1)
		return (0);
	return (1);
}