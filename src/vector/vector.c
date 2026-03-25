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

t_vec	vector_create_short(double x, double y, double z)
{
	return ((t_vec){x, y, z});
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

t_vec	vector_scale(t_vec vec, double scalar)
{
	return ((t_vec){vec.x * scalar, vec.y * scalar, vec.z * scalar});
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
