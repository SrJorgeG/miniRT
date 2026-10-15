/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:14:28 by dcid-san          #+#    #+#             */
/*   Updated: 2026/04/05 21:02:37 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	hit_cyl_body_aux(t_hit_cyl_body_data *data, t_vec oc, t_object *obj,
		t_ray ray)
{
	double		t;
	t_cylinder	*cyl;

	cyl = obj->object;
	t = (-data->coords.y - sqrt(data->discriminant)) / (2.0 * data->coords.x);
	if (t > 1e-6)
	{
		data->h = vector_dot_prod(vector_sum(oc,
					vector_multiplication(ray.direction, t)), obj->orientation);
		if (fabs(data->h) <= cyl->half_h)
			return (t);
	}
	t = (-data->coords.y + sqrt(data->discriminant)) / (2.0 * data->coords.x);
	if (t > 1e-6)
	{
		data->h = vector_dot_prod(vector_sum(oc,
					vector_multiplication(ray.direction, t)), obj->orientation);
		if (fabs(data->h) <= cyl->half_h)
			return (t);
	}
	return (-1);
}

static double	hit_cylinder_body(t_ray ray, t_object *obj, t_vec oc,
		t_cylinder *cyl)
{
	t_hit_cyl_body_data	data;

	data.coords.x = vector_dot_prod(ray.direction, ray.direction)
		- pow(vector_dot_prod(ray.direction, obj->orientation), 2);
	data.coords.y = 2.0 * (vector_dot_prod(ray.direction, oc)
			- vector_dot_prod(ray.direction, obj->orientation)
			* vector_dot_prod(oc, obj->orientation));
	data.coords.z = vector_dot_prod(oc, oc) - pow(vector_dot_prod(oc,
				obj->orientation), 2) - cyl->radius * cyl->radius;
	data.discriminant = data.coords.y * data.coords.y - 4 * data.coords.x
		* data.coords.z;
	if (data.discriminant < 0)
		return (-1);
	return (hit_cyl_body_aux(&data, oc, obj, ray));
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
	double	t_body;
	double	t_cap;

	oc = vector_rest(ray.origin, cyl->center);
	cyl->radius = cyl->diameter / 2.0;
	cyl->half_h = cyl->height / 2.0;
	t_body = hit_cylinder_body(ray, obj, oc, cyl);
	t_cap = hit_cylinder_caps(ray, obj);
	if (t_body > 0 && t_cap > 0)
		*obj_distance = fmin(t_body, t_cap);
	else if (t_body > 0)
		*obj_distance = t_body;
	else if (t_cap > 0)
		*obj_distance = t_cap;
	else
		return (0);
	return (1);
}
