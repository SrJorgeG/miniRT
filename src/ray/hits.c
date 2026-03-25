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

	oc = vector_rest(ray.origin, sphere->center);
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

	eps = 1e-6;
	denom = vector_dot_prod(ray.direction, plane->vector);
	if (fabs(denom) > eps)
	{
		temp = vector_rest(plane->point, ray.origin);
		t = vector_dot_prod(temp, plane->vector) / denom;
		if (t > eps)
		{
			*obj_distance = t;
			return (1);
		}
	}
	return (0);
}

void	get_cylinder_normal(t_hit *hit, t_object *obj, t_cylinder *cyl,
		t_ray ray)
{
	t_vec	to_hit;
	double	h;
	double	half_h;
	t_vec	proj;

	to_hit = vector_rest(hit->p, cyl->center);
	h = vector_dot_prod(to_hit, obj->orientation);
	half_h = cyl->height / 2.0;
	if (fabs(fabs(h) - half_h) < 1e-3)
	{
		hit->normal = obj->orientation;
		if (h < 0)
			hit->normal = vector_multiplication(hit->normal, -1.0);
	}
	else
	{
		proj = vector_multiplication(obj->orientation, h);
		hit->normal = vector_normalize(vector_rest(to_hit, proj));
	}
	if (vector_dot_prod(ray.direction, hit->normal) > 0)
		hit->normal = vector_multiplication(hit->normal, -1.0);
}

int	hit_cylinder(t_ray ray, t_object *obj, t_cylinder *cyl,
		double *obj_distance)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;

	(void)obj_distance;
	oc = vector_rest(ray.origin, cyl->center);
	a = vector_dot_prod(ray.direction, ray.direction);
	a = a - pow(vector_dot_prod(ray.direction, obj->orientation), 2);
	b = vector_dot_prod(ray.direction, oc);
	b = 2.0 * (b - vector_dot_prod(ray.direction, obj->orientation)
			* vector_dot_prod(oc, obj->orientation));
	c = vector_dot_prod(oc, oc);
	c = c - pow(vector_dot_prod(oc, obj->orientation), 2);
	c = c - (cyl->diameter / 2.0) * (cyl->diameter / 2.0);
	if (b * b - 4 * a * c < 0)
		return (0);
	return (0);
}
