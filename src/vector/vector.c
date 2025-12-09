/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/17 15:30:17 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


t_vec   v(double x, double y, double z)
{
	return ((t_vec) {x, y, z});
}

t_vec	*vector_constructor(double x, double y, double z)
{
	t_vec	*vector;

	vector = malloc(sizeof(t_vec));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

inline void	v_free(t_vec	*vector)
{
	free(vector);
}

t_vec	create_vector(char *vector_str)
{
	char	**vector_split;
	t_vec	vector;

	vector_split = ft_split(vector_str, ',');
	vector.x = ft_atoi(vector_split[0]);
	vector.y = ft_atoi(vector_split[1]);
	vector.z = ft_atoi(vector_split[2]);
	ft_free_split(vector_split);
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

int is_normalized_vec(t_vec *vector)
{
	if (vector->x < -1 || vector->x > 1)
		return (0);
	if (vector->y < -1 || vector->y > 1)
		return (0);
	if (vector->z < -1 || vector->z > 1)
		return (0);
	return (1);
}
