/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:12:05 by krusty            #+#    #+#             */
/*   Updated: 2026/03/25 19:12:05 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	hit_sphere(t_ray ray, t_sphere *sphere, double *obj_distance)
{
	t_vec	oc;
	t_vec	equation;
	double	discriminant;
	double	sqrt_disc;
	t_vec	transformed_center;

	transformed_center.x = sphere->center.x + sphere->trans_x;
	transformed_center.y = sphere->center.y + sphere->trans_y;
	transformed_center.z = sphere->center.z + sphere->trans_z;
	oc = vector_rest(ray.origin, transformed_center);
	equation.y = 2.0 * vector_dot_prod(oc, ray.direction);
	equation.z = vector_dot_prod(oc, oc) - sphere->radius * sphere->radius;
	discriminant = equation.y * equation.y - 4.0 * equation.z;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrt(discriminant);
	if ((-equation.y - sqrt_disc) / 2.0 > 0.0001)
	{
		*obj_distance = (-equation.y - sqrt_disc) / 2.0;
		return (1);
	}
	if ((-equation.y + sqrt_disc) / 2.0 > 0.0001)
	{
		*obj_distance = (-equation.y + sqrt_disc) / 2.0;
		return (1);
	}
	return (0);
}

int	hit_plane(t_ray ray, t_plane *plane, double *obj_distance)
{
	double	denom;
	double	t;
	double	eps;
	t_vec	temp;
	t_vec	transformed_point;
	t_vec	transformed_normal;

	eps = 1e-6;
	transformed_point.x = plane->point.x + plane->trans_x;
	transformed_point.y = plane->point.y + plane->trans_y;
	transformed_point.z = plane->point.z + plane->trans_z;
	transformed_normal = transform_normal(plane->vector, plane->rot_x,
			plane->rot_y, plane->rot_z);
	denom = vector_dot_prod(ray.direction, transformed_normal);
	if (fabs(denom) > eps)
	{
		temp = vector_rest(transformed_point, ray.origin);
		t = vector_dot_prod(temp, transformed_normal) / denom;
		if (t > eps)
		{
			*obj_distance = t;
			return (1);
		}
	}
	return (0);
}
