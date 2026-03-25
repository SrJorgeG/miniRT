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

t_ray	*ray_constructor(t_point *origin, t_vec *direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->origin = *origin;
	ray->direction = *direction;
	return (ray);
}

void	ray_destructor(t_ray *ray)
{
	free(ray);
}

t_vec	ray_generate_points(t_ray ray, long t_param)
{
	return (vector_sum(ray.origin,
			vector_multiplication(ray.direction, t_param)));
}
