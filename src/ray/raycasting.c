/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:07:06 by dcid-san          #+#    #+#             */
/*   Updated: 2026/01/05 16:07:06 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	hit_object(t_ray ray, t_object *object, double *obj_distance)
{
	if (object->type == SPHERE)
		return (hit_sphere(ray, object->object, obj_distance));
	else if (object->type == CYLINDER)
		return (hit_cylinder(ray, object, object->object, obj_distance));
	else if (object->type == PLANE)
		return (hit_plane(ray, object->object, obj_distance));
	return (0);
}

void	fill_hit_info(t_hit *closest, double obj_distance, t_object *last_hit)
{
	closest->object = last_hit;
	closest->color = last_hit->color_range;
	closest->t = obj_distance;
	closest->hit = 1;
}

void	get_hit_normal(t_hit *hit, t_ray ray)
{
	t_sphere	*sphere;
	t_plane		*plane;

	if (hit->object->type == SPHERE)
	{
		sphere = hit->object->object;
		hit->normal = vector_normalize(vector_rest(hit->p, sphere->center));
	}
	else if (hit->object->type == PLANE)
	{
		plane = hit->object->object;
		hit->normal = plane->vector;
		if (vector_dot_prod(ray.direction, hit->normal) > 0)
			hit->normal = vector_multiplication(hit->normal, -1.0);
	}
	else if (hit->object->type == CYLINDER)
		get_cylinder_normal(hit, hit->object, hit->object->object, ray);
}

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
	current = scene->map.objects->first;
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
	check_all_hits(scene, ray, &closest, scene->map.last_hit);
	if (closest.hit)
	{
		scene->map.last_hit = closest.object;
		closest.p = vector_sum(ray.origin,
				vector_multiplication(ray.direction, closest.t));
		get_hit_normal(&closest, ray);
	}
	return (closest);
}
