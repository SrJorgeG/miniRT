/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:07:06 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 21:05:08 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_ray	get_ray_from_pixel(t_scene *scene, t_vec image_center,
		t_vec pixel_center)
{
	t_vec	x_offset;
	t_vec	y_offset;
	t_vec	pixel_world;

	x_offset = vector_multiplication(scene->map->camera.right, pixel_center.x);
	y_offset = vector_multiplication(scene->map->camera.up, pixel_center.y);
	pixel_world = vector_sum(image_center, vector_sum(x_offset, y_offset));
	return ((t_ray){scene->map->camera.view_point,
		vector_normalize(vector_rest(pixel_world,
				scene->map->camera.view_point))});
}

t_vec	find_pixel_on_viewport(int x, int y, t_scene *scene)
{
	t_real	u;
	t_real	v;

	u = (x + 0.5) / (t_real)scene->screen_w;
	v = (y + 0.5) / (t_real)scene->screen_h;
	return ((t_vec){(u - 0.5) * scene->viewport_w,
		(v - 0.5) * scene->viewport_h, 0});
}
