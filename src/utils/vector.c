/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:49 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector	*create_vector(char *vector_str)
{
	char	**vector_split;
	t_vector	*vector;
	
	vector_split = ft_split(vector_str, ',');
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = ft_atoi(vector_split[0]);	
	vector->y = ft_atoi(vector_split[1]);	
	vector->z = ft_atoi(vector_split[2]);
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