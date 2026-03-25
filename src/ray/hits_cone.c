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

int	hit_cone(t_ray ray, t_object *obj, t_cone *cone, double *obj_distance)
{
	t_vec	coeff;
	double	discriminant;
	double	sqrt_disc;

	calc_cone_coeff(ray, obj, cone, &coeff);
	discriminant = coeff.y * coeff.y - 4.0 * coeff.x * coeff.z;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrt(discriminant);
	if ((-coeff.y - sqrt_disc) / (2.0 * coeff.x) > 0.0001)
		return (*obj_distance = (-coeff.y - sqrt_disc) / (2.0 * coeff.x), 1);
	if ((-coeff.y + sqrt_disc) / (2.0 * coeff.x) > 0.0001)
		return (*obj_distance = (-coeff.y + sqrt_disc) / (2.0 * coeff.x), 1);
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
	hit->normal = vector_sum(rad_vec, vector_multiplication(obj->orientation,
			vector_lenght(rad_vec) / k));
	hit->normal = vector_normalize(hit->normal);
	if (vector_dot_prod(ray.direction, hit->normal) > 0)
		hit->normal = vector_multiplication(hit->normal, -1.0);
}
