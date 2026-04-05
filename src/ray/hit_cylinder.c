/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:12:05 by krusty            #+#    #+#             */
/*   Updated: 2026/03/25 19:12:05 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static double	check_body_t(t_ray ray, t_object *obj,
		t_cylinder *cyl, double t, t_vec trans_center)
{
	double	h;
	t_vec	oc;
	t_vec	p;

	if (t > 1e-6)
	{
		oc = vector_rest(ray.origin, trans_center);
		p = vector_sum(oc, vector_multiplication(ray.direction, t));
		h = vector_dot_prod(p, obj->orientation);
		if (fabs(h) <= cyl->height / 2.0)
			return (t);
	}
	return (-1);
}

static double	hit_cyl_body(t_ray ray, t_object *obj, t_cylinder *cyl,
		t_vec trans_center)
{
	t_vec	oc;
	double	abc[3];
	double	disc;
	double	t;

	oc = vector_rest(ray.origin, trans_center);
	abc[0] = vector_dot_prod(ray.direction, ray.direction)
		- pow(vector_dot_prod(ray.direction, obj->orientation), 2);
	abc[1] = 2.0 * (vector_dot_prod(ray.direction, oc)
			- vector_dot_prod(ray.direction, obj->orientation)
			* vector_dot_prod(oc, obj->orientation));
	abc[2] = vector_dot_prod(oc, oc)
		- pow(vector_dot_prod(oc, obj->orientation), 2)
		- (cyl->diameter / 2.0) * (cyl->diameter / 2.0);
	disc = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (disc < 0)
		return (-1);
	t = check_body_t(ray, obj, cyl, (-abc[1] - sqrt(disc)) / (2.0 * abc[0]),
			trans_center);
	if (t > 0)
		return (t);
	t = (-abc[1] + sqrt(disc)) / (2.0 * abc[0]);
	return (check_body_t(ray, obj, cyl, t, trans_center));
}

static double	check_cap(t_ray ray, t_vec center, t_vec normal, double r)
{
	double	denom;
	double	t;
	t_vec	p;
	t_vec	v;

	denom = vector_dot_prod(ray.direction, normal);
	if (fabs(denom) < 1e-6)
		return (-1);
	t = vector_dot_prod(vector_rest(center, ray.origin), normal) / denom;
	if (t < 1e-6)
		return (-1);
	p = vector_sum(ray.origin, vector_multiplication(ray.direction, t));
	v = vector_rest(p, center);
	if (vector_dot_prod(v, v) <= (r * r))
		return (t);
	return (-1);
}

void	get_cylinder_normal(t_hit *hit, t_object *obj, t_cylinder *cyl,
		t_ray ray)
{
	t_vec	to_hit;
	double	h;
	double	half_h;
	t_vec	proj;
	t_vec	trans_center;
	t_vec	trans_axis;

	trans_center.x = cyl->center.x + cyl->trans_x;
	trans_center.y = cyl->center.y + cyl->trans_y;
	trans_center.z = cyl->center.z + cyl->trans_z;
	trans_axis = transform_normal(obj->orientation, cyl->rot_x, cyl->rot_y,
			cyl->rot_z);
	to_hit = vector_rest(hit->p, trans_center);
	h = vector_dot_prod(to_hit, trans_axis);
	half_h = cyl->height / 2.0;
	if (fabs(fabs(h) - half_h) < 1e-3)
	{
		hit->normal = trans_axis;
		if (h < 0)
			hit->normal = vector_multiplication(hit->normal, -1.0);
	}
	else
	{
		proj = vector_multiplication(trans_axis, h);
		hit->normal = vector_normalize(vector_rest(to_hit, proj));
	}
	if (vector_dot_prod(ray.direction, hit->normal) > 0)
		hit->normal = vector_multiplication(hit->normal, -1.0);
}

int	hit_cylinder(t_ray ray, t_object *obj, t_cylinder *cyl,
		double *obj_distance)
{
	double	t_min;
	double	t_temp;
	t_vec	top_cap;
	t_vec	bot_cap;
	t_vec	down_norm;
	t_vec	trans_center;
	t_vec	trans_axis;

	trans_center.x = cyl->center.x + cyl->trans_x;
	trans_center.y = cyl->center.y + cyl->trans_y;
	trans_center.z = cyl->center.z + cyl->trans_z;
	trans_axis = transform_normal(obj->orientation, cyl->rot_x, cyl->rot_y,
			cyl->rot_z);
	t_min = hit_cyl_body(ray, obj, cyl, trans_center);
	top_cap = vector_sum(trans_center,
			vector_multiplication(trans_axis, cyl->height / 2.0));
	bot_cap = vector_rest(trans_center,
			vector_multiplication(trans_axis, cyl->height / 2.0));
	t_temp = check_cap(ray, top_cap, trans_axis, cyl->diameter / 2.0);
	if (t_temp > 0 && (t_min < 0 || t_temp < t_min))
		t_min = t_temp;
	down_norm = vector_multiplication(trans_axis, -1.0);
	t_temp = check_cap(ray, bot_cap, down_norm, cyl->diameter / 2.0);
	if (t_temp > 0 && (t_min < 0 || t_temp < t_min))
		t_min = t_temp;
	if (t_min > 0)
	{
		*obj_distance = t_min;
		return (1);
	}
	return (0);
}
