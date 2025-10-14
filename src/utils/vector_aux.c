/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:58:42 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/14 19:27:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

inline double	lenght2(t_vector *vec)
{
	return (sqrt(vec->x) + sqrt(vec->y) + sqrt(vec->z));
}

inline double	lenght(t_vector *vec)
{
	return (sqrt(lenght2(vec)));
}

t_vector	*normalize(t_vector *vec)
{
	t_vector	*vector;
	double		len;
	
	len = lenght(vec);
	if (!len)
		return (NULL);
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = vec->x / len;
	vector->y = vec->y / len;
	vector->z = vec->z / len;
	return (vector);
}

double	dot_prod(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);	
}

t_vector	*cross_prod(t_vector *v1, t_vector *v2)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = v1->y * v2->z - v1->z * v2->y;
	vector->y = v1->z * v2->x - v1->x * v2->z;
	vector->z =	v1->x * v2->y - v1->y * v2->x;
	return (vector);
}
