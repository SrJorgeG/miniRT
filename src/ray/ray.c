/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:33:47 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/17 21:50:20 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_rayo	*ray_constructor(t_point *origin ,t_vector *direction)
{
	t_rayo	*ray;
	
	ray = malloc(sizeof(t_rayo));
	if (!ray)
		return (NULL);
	ray->origin = origin;
	ray->direction = direction;
	return (ray);
}

void	ray_destructor(t_rayo *ray)
{
	vector_destructor(ray->direction);
	vector_destructor(ray->origin);
	free(ray);
}

// CALCULAR / GENERAR PUNTOS EN UN RAYO A PARTIR DE UNA VARIABLE T
t_point	*ray_generate_points(t_rayo *ray, long t)
{
	t_vector	*a;
	t_point		*b;
	
	a = vector_multiplication(ray->direction, t);
	if (!a)
		return (NULL);
	b = vector_sum(ray->origin, a);
	if (!b)
	{
		free(a);
		return (NULL);
	}
	free(a);
	return (b);
}
