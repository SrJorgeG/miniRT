/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:07:06 by dcid-san          #+#    #+#             */
/*   Updated: 2026/01/05 16:07:06 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	add_ambient_light(t_color *final_color, t_hit *hit,
		t_scene *scene, t_color base_color)
{
	*final_color = color_multiply(base_color, scene->map.amb_ligt.amb_col);
	*final_color = color_scale(*final_color, scene->map.amb_ligt.amb_ratio);
}

void	add_diffuse_lighting(t_color *final_color, t_hit *hit,
		t_scene *scene, t_color base_color)
{
	t_light	*current_light;
	t_list	*current;
	t_vec	light_dir;
	double	diffuse_factor;
	t_color	diffuse_for_this_light;

	current = scene->map.lights->first;
	while (current)
	{
		current_light = scene->map.lights->first->content;
		light_dir = vector_normalize(vector_rest(current_light->light_point,
				hit->p));
		diffuse_factor = vector_dot_prod(hit->normal, light_dir);
		if (diffuse_factor < 0)
			diffuse_factor = 0;
		diffuse_for_this_light = color_multiply(base_color,
				current_light->color_range);
		diffuse_for_this_light = color_scale(diffuse_for_this_light,
				current_light->brightness * diffuse_factor);
		*final_color = color_add(*final_color, diffuse_for_this_light);
		current = current->next;
	}
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
