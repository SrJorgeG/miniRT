/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:07:06 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 21:05:08 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	add_ambient_light(t_color *final_color, t_hit *hit,
		t_scene *scene, t_color base_color)
{
	(void)hit;
	*final_color = color_multiply(base_color, scene->map->amb_ligt.amb_col);
	*final_color = color_scale(*final_color, scene->map->amb_ligt.amb_ratio);
}

static void	apply_light(t_color c[2], t_hit *hit,
		t_scene *scene, t_light *current_light)
{
	t_vec	light_dir;
	double	light_distance;
	double	diffuse_factor;
	t_ray	shadow_ray;
	t_color	diffuse;

	light_dir = vector_rest(current_light->light_point, hit->p);
	light_distance = vector_lenght(light_dir);
	light_dir = vector_normalize(light_dir);
	shadow_ray.origin = vector_sum(hit->p,
			vector_multiplication(hit->normal, 1e-4));
	shadow_ray.direction = light_dir;
	if (!is_in_shadow(scene, shadow_ray, light_distance))
	{
		diffuse_factor = vector_dot_prod(hit->normal, light_dir);
		if (diffuse_factor < 0)
			diffuse_factor = 0;
		diffuse = color_multiply(c[1], current_light->color_range);
		diffuse = color_scale(diffuse,
				current_light->brightness * diffuse_factor);
		c[0] = color_add(c[0], diffuse);
	}
}

void	add_diffuse_lighting(t_color *final_color, t_hit *hit,
		t_scene *scene, t_color base_color)
{
	t_light	*current_light;
	t_list	*current;
	t_color	c[2];

	c[0] = *final_color;
	c[1] = base_color;
	current = scene->map->lights->first;
	while (current)
	{
		current_light = current->content;
		apply_light(c, hit, scene, current_light);
		current = current->next;
	}
	*final_color = c[0];
}

t_color	calculate_lighting(t_hit *hit, t_scene *scene)
{
	t_color	base_color;
	t_color	final_color;

	base_color = textures_handler(hit, scene);
	add_ambient_light(&final_color, hit, scene, base_color);
	add_diffuse_lighting(&final_color, hit, scene, base_color);
	return (final_color);
}
