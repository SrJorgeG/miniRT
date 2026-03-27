/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:00 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 21:05:38 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	debug_camera(t_camera *cam)
{
	printf("=== CAMERA ===\n");
	debug_vec("view_point", cam->view_point);
	debug_vec("orientation", cam->orientation_nor);
	debug_vec("right", cam->right);
	debug_vec("up", cam->up);
	printf("fov: %d\n", cam->fov);
	printf("focal: %u\n", cam->focal);
	printf("radial_fov: %.4f\n", cam->radial_fov);
}

void	debug_ambient(t_amb_light *amb)
{
	printf("=== AMBIENT LIGHT ===\n");
	printf("ratio: %.4f\n", amb->amb_ratio);
	debug_color("color", amb->amb_col);
}

void	debug_light(t_light *light)
{
	printf("=== LIGHT ===\n");
	debug_vec("position", light->light_point);
	printf("brightness: %.4f\n", light->brightness);
	debug_color("color", light->color_range);
}

void	debug_scene(t_scene *scene)
{
	printf("\n======= SCENE DEBUG =======\n");
	printf("screen: %dx%d\n", scene->screen_w, scene->screen_h);
	printf("aspect: %.4f\n", scene->aspect);
	printf("viewport: %.4f\n", scene->viewport);
	printf("viewport_w: %.4f\n", scene->viewport_w);
	printf("viewport_h: %.4f\n", scene->viewport_h);
	printf("cache_count: %d\n", scene->cache_count);
	debug_map(scene->map);
}

void	debug_map(t_map *map)
{
	t_list	*tmp;
	t_light	*light;

	printf("\n======= MAP DEBUG =======\n");
	printf("has_camera: %d\n", map->has_camera);
	printf("has_ambient: %d\n", map->has_amb_ligt);
	printf("has_lights: %d\n", map->has_lights);
	if (map->has_camera)
		debug_camera(&map->camera);
	if (map->has_amb_ligt)
		debug_ambient(&map->amb_ligt);
	if (map->has_lights)
	{
		tmp = map->lights->first;
		while (tmp)
		{
			light = (t_light *)tmp->content;
			debug_light(light);
			tmp = tmp->next;
		}
	}
	debug_objects(map->objects);
}
