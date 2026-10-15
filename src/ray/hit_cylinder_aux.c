/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:57:01 by dcid-san          #+#    #+#             */
/*   Updated: 2026/04/05 20:58:50 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	hit_caps_aux(t_hit_cyl_caps_data *data, t_object *obj, t_ray *ray)
{
	t_cylinder	*cyl;

	cyl = obj->object;
	data->cap_center = vector_sum(cyl->center,
			vector_multiplication(obj->orientation, cyl->half_h));
	data->t = vector_dot_prod(vector_rest(data->cap_center, ray->origin),
			obj->orientation) / data->denom;
	if (data->t > 1e-6)
	{
		data->hit = vector_sum(ray->origin,
				vector_multiplication(ray->direction, data->t));
		data->dist = vector_lenght(vector_rest(data->hit, data->cap_center));
		if (data->dist <= cyl->radius)
			data->closest = data->t;
	}
	data->cap_center = vector_sum(cyl->center,
			vector_multiplication(obj->orientation, cyl->half_h));
}

double	hit_cylinder_caps(t_ray ray, t_object *obj)
{
	t_hit_cyl_caps_data	data;
	t_cylinder			*cyl;

	cyl = obj->object;
	data.denom = vector_dot_prod(ray.direction, obj->orientation);
	if (fabs(data.denom) < 1e-6)
		return (-1);
	data.closest = INFINITY;
	hit_caps_aux(&data, obj, &ray);
	data.t = vector_dot_prod(vector_rest(data.cap_center, ray.origin),
			obj->orientation) / data.denom;
	if (data.t > 1e-6 && data.t < data.closest)
	{
		data.hit = vector_sum(ray.origin, vector_multiplication(ray.direction,
					data.t));
		data.dist = vector_lenght(vector_rest(data.hit, data.cap_center));
		if (data.dist <= cyl->radius)
			data.closest = data.t;
	}
	if (data.closest == INFINITY)
		return (-1);
	return (data.closest);
}
