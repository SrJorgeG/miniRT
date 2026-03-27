/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:58:42 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/17 15:29:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

inline double	vector_lenght_square(t_vec *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

inline double	vector_lenght(t_vec vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_vec	vector_normalize(t_vec vec)
{
	double	len;

	len = vector_lenght(vec);
	if (len < 0.0000001)
		return ((t_vec){0, 1, 0});
	return ((t_vec){vec.x / len, vec.y / len, vec.z / len});
}

double	vector_dot_prod(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vector_cross_prod(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x});
}
