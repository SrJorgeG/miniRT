/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:07:06 by dcid-san          #+#    #+#             */
/*   Updated: 2026/04/05 20:59:30 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	check_all_hits(t_scene *scene, t_ray ray, t_hit *closest,
		t_object *last_hit)
{
	t_list		*current;
	t_object	*obj;
	double		obj_distance;

	if (last_hit)
	{
		if (hit_object(ray, last_hit, &obj_distance)
			&& obj_distance < closest->t)
		{
			if (obj_distance < closest->t)
				fill_hit_info(closest, obj_distance, last_hit);
		}
	}
	current = scene->map->objects->first;
	while (current)
	{
		obj = current->content;
		if (obj != last_hit && hit_object(ray, obj, &obj_distance)
			&& obj_distance < closest->t)
			fill_hit_info(closest, obj_distance, obj);
		current = current->next;
	}
}

t_hit	get_hits(t_scene *scene, t_ray ray)
{
	t_hit	closest;

	closest.hit = 0;
	closest.t = INFINITY;
	check_all_hits(scene, ray, &closest, scene->map->last_hit);
	if (closest.hit)
	{
		scene->map->last_hit = closest.object;
		closest.p = vector_sum(ray.origin,
				vector_multiplication(ray.direction, closest.t));
		get_hit_normal(&closest, ray);
	}
	return (closest);
}

int	is_in_shadow(t_scene *scene, t_ray shadow_ray, double light_distance)
{
	t_hit	closest;

	closest.hit = 0;
	closest.t = INFINITY;
	check_all_hits(scene, shadow_ray, &closest, NULL);
	if (closest.hit && closest.t > 1e-4 && closest.t < light_distance)
		return (1);
	return (0);
}
