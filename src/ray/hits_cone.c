/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hits_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:12:05 by krusty            #+#    #+#             */
/*   Updated: 2026/03/25 19:12:05 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	calc_cone_coeff(t_ray ray, t_object *obj, t_cone *cone,
			t_vec *coeff)
{
	t_vec	oc;
	double	k;

	k = tan(atan((cone->diameter / 2.0) / cone->height));
	oc = vector_rest(ray.origin, cone->top);
	coeff->x = vector_dot_prod(ray.direction, ray.direction);
	coeff->x -= pow(vector_dot_prod(ray.direction, obj->orientation), 2)
		* (1.0 + k * k);
	coeff->y = 2.0 * (vector_dot_prod(ray.direction, oc)
			- vector_dot_prod(ray.direction, obj->orientation)
			* vector_dot_prod(oc, obj->orientation) * (1.0 + k * k));
	coeff->z = vector_dot_prod(oc, oc);
	coeff->z -= pow(vector_dot_prod(oc, obj->orientation), 2) * (1.0 + k * k);
}

static int	is_valid_cone_hit(t_ray ray, t_object *obj, t_cone *cone,
			double t)
{
	t_vec	hit_point;
	t_vec	to_hit;
	double	h;

	hit_point = vector_sum(ray.origin, vector_multiplication(ray.direction, t));
	to_hit = vector_rest(hit_point, cone->top);
	h = vector_dot_prod(to_hit, obj->orientation);
	return (h >= 0 && h <= cone->height);
}

int	hit_cone(t_ray ray, t_object *obj, t_cone *cone, double *obj_distance)
{
	t_vec	coeff;
	double	discriminant;
	double	sqrt_disc;
	double	t1;
	double	t2;

	calc_cone_coeff(ray, obj, cone, &coeff);
	discriminant = coeff.y * coeff.y - 4.0 * coeff.x * coeff.z;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrt(discriminant);
	t1 = (-coeff.y - sqrt_disc) / (2.0 * coeff.x);
	t2 = (-coeff.y + sqrt_disc) / (2.0 * coeff.x);
	if (t1 > 0.0001 && is_valid_cone_hit(ray, obj, cone, t1))
		return (*obj_distance = t1, 1);
	if (t2 > 0.0001 && is_valid_cone_hit(ray, obj, cone, t2))
		return (*obj_distance = t2, 1);
	return (0);
}

void	get_cone_normal(t_hit *hit, t_object *obj, t_cone *cone, t_ray ray)
{
	t_vec	to_hit;
	t_vec	proj;
	t_vec	rad_vec;
	double	h;
	double	k;

	k = tan(atan((cone->diameter / 2.0) / cone->height));
	to_hit = vector_rest(hit->p, cone->top);
	h = vector_dot_prod(to_hit, obj->orientation);
	proj = vector_multiplication(obj->orientation, h);
	rad_vec = vector_rest(to_hit, proj);
	k = vector_lenght(rad_vec) / k;
	hit->normal = vector_sum(rad_vec,
			vector_multiplication(obj->orientation, k));
	hit->normal = vector_normalize(hit->normal);
	if (vector_dot_prod(ray.direction, hit->normal) > 0)
		hit->normal = vector_multiplication(hit->normal, -1.0);
}
