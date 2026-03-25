/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:34:34 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/17 21:47:56 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec	vector_sum(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec	vector_rest(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec	vector_multiplication(t_vec v1, double num)
{
	return ((t_vec){v1.x * num, v1.y * num, v1.z * num});
}

t_vec	vector_division(t_vec v1, double num)
{
	return ((t_vec){v1.x / num, v1.y / num, v1.z / num});
}

t_vec	*vector_dup(t_vec vec)
{
	t_vec	*dup;

	dup = malloc(sizeof(t_vec));
	if (!dup)
		return (NULL);
	dup->x = vec.x;
	dup->y = vec.y;
	dup->z = vec.z;
	return (dup);
}
