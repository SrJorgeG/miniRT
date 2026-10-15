/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:30:00 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:30:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	in_body(t_ray ray, t_object *obj, t_cylinder *cyl, double t)
{
	t_vec	p;
	double	h;

	if (t <= 0.0001)
		return (0);
	p = vector_sum(ray.origin, vector_multiplication(ray.direction, t));
	h = vector_dot_prod(vector_rest(p, cyl->center), obj->orientation);
	return (fabs(h) <= cyl->height / 2.0);
}

static double	hit_body(t_ray ray, t_object *obj, t_cylinder *cyl)
{
	t_vec	oc;
	t_vec	q;
	double	dd;
	double	disc;

	oc = vector_rest(ray.origin, cyl->center);
	dd = vector_dot_prod(ray.direction, obj->orientation);
	q.x = vector_dot_prod(ray.direction, ray.direction) - dd * dd;
	q.y = 2.0 * (vector_dot_prod(ray.direction, oc)
			- dd * vector_dot_prod(oc, obj->orientation));
	q.z = vector_dot_prod(oc, oc) - pow(vector_dot_prod(oc, obj->orientation),
			2) - (cyl->diameter / 2.0) * (cyl->diameter / 2.0);
	disc = q.y * q.y - 4.0 * q.x * q.z;
	if (fabs(q.x) < 1e-12 || disc < 0)
		return (-1.0);
	disc = sqrt(disc);
	if (in_body(ray, obj, cyl, (-q.y - disc) / (2.0 * q.x)))
		return ((-q.y - disc) / (2.0 * q.x));
	if (in_body(ray, obj, cyl, (-q.y + disc) / (2.0 * q.x)))
		return ((-q.y + disc) / (2.0 * q.x));
	return (-1.0);
}

static double	hit_cap(t_ray ray, t_object *obj, t_cylinder *cyl, double side)
{
	t_vec	cap;
	t_vec	p;
	double	denom;
	double	t;

	cap = vector_sum(cyl->center, vector_multiplication(obj->orientation,
				side * cyl->height / 2.0));
	denom = vector_dot_prod(ray.direction, obj->orientation);
	if (fabs(denom) < 1e-9)
		return (-1.0);
	t = vector_dot_prod(vector_rest(cap, ray.origin), obj->orientation)
		/ denom;
	if (t <= 0.0001)
		return (-1.0);
	p = vector_rest(vector_sum(ray.origin,
				vector_multiplication(ray.direction, t)), cap);
	if (vector_dot_prod(p, p) > pow(cyl->diameter / 2.0, 2))
		return (-1.0);
	return (t);
}

int	hit_cylinder(t_ray ray, t_object *obj, t_cylinder *cyl,
		double *obj_distance)
{
	double	t[3];
	double	best;
	int		i;

	t[0] = hit_body(ray, obj, cyl);
	t[1] = hit_cap(ray, obj, cyl, 1.0);
	t[2] = hit_cap(ray, obj, cyl, -1.0);
	best = -1.0;
	i = -1;
	while (++i < 3)
		if (t[i] > 0 && (best < 0 || t[i] < best))
			best = t[i];
	if (best < 0)
		return (0);
	*obj_distance = best;
	return (1);
}
