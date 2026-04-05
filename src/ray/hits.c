/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:14:21 by dcid-san          #+#    #+#             */
/*   Updated: 2026/04/05 20:55:40 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	hit_sphere(t_ray ray, t_sphere *sphere, double *obj_distance)
{
	t_vec	oc;
	t_vec	equation;
	double	discriminant;
	double	sqrt_disc;
	t_vec2	data;

	oc = vector_rest(ray.origin, sphere->center);
	equation.y = 2.0 * vector_dot_prod(oc, ray.direction);
	equation.z = vector_dot_prod(oc, oc) - sphere->radius * sphere->radius;
	discriminant = equation.y * equation.y - 4.0 * equation.z;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrt(discriminant);
	data.x = (-equation.y - sqrt_disc) / 2.0;
	data.y = (-equation.y + sqrt_disc) / 2.0;
	if (data.x > 0.0001)
		return (*obj_distance = data.x, 1);
	if (data.y > 0.0001)
		return (*obj_distance = data.y, 1);
	return (0);
}

int	hit_plane(t_ray ray, t_plane *plane, double *obj_distance)
{
	double	denom;
	double	t;
	double	eps;

	eps = 1e-6;
	denom = vector_dot_prod(ray.direction, plane->vector);
	if (fabs(denom) > eps)
	{
		t = vector_dot_prod(vector_rest(plane->point, ray.origin),
				plane->vector) / denom;
		if (t > eps)
		{
			*obj_distance = t;
			return (1);
		}
	}
	return (0);
}
