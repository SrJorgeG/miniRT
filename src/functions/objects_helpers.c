/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:00 by dcid-san          #+#    #+#             */
/*   Updated: 2025/03/25 12:00:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	resize_helper(t_object *obj, int is_bigger)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	if (obj->type == SPHERE)
	{
		sphere = obj->object;
		if (is_bigger)
			sphere->radius += 1;
		else
			sphere->radius -= 1;
	}
	if (obj->type == CYLINDER)
	{
		cylinder = obj->object;
		if (is_bigger)
			cylinder->diameter += 1;
		else
			cylinder->diameter -= 1;
	}
}

void	move_helper(t_object *obj, double x_val, double y_val)
{
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;

	if (obj->type == SPHERE)
	{
		sphere = obj->object;
		sphere->center.x += x_val;
		sphere->center.y += y_val;
	}
	if (obj->type == CYLINDER)
	{
		cylinder = obj->object;
		cylinder->center.x += x_val;
		cylinder->center.y += y_val;
	}
	if (obj->type == PLANE)
	{
		plane = obj->object;
		plane->point.x += x_val;
		plane->point.y += y_val;
	}
}

void	clamp_orientation(t_vec *orientation)
{
	if (orientation->x > 1.0)
		orientation->x = 0;
	if (orientation->x < -1.0)
		orientation->x = 1.0;
	if (orientation->y > 1.0)
		orientation->y = 0;
	if (orientation->y < -1.0)
		orientation->y = 1.0;
	if (orientation->z > 1.0)
		orientation->z = 0;
	if (orientation->z < -1.0)
		orientation->z = 1.0;
}

void	brighten_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixel;
	int		rgb[3];

	pixel = &image->pixels[(y * image->width + x) * 4];
	rgb[0] = (uint8_t)((float)pixel[0] * 1.4f);
	rgb[1] = (uint8_t)((float)pixel[1] * 1.4f);
	rgb[2] = (uint8_t)((float)pixel[2] * 1.4f);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	mlx_put_pixel(image, x, y,
		color_to_int_no_alpha((t_color){rgb[0], rgb[1], rgb[2]}));
}

void	restore_pixel(t_scene *scene, mlx_image_t *img, uint32_t x, uint32_t y)
{
	t_hit	hit;
	t_ray	ray;
	t_vec	pv;

	pv = find_pixel_on_viewport(x, y, scene);
	ray = get_ray_from_pixel(scene, scene->image_center, pv);
	hit = get_hits(scene, ray);
	mlx_put_pixel(img, x, y,
		color_to_int_no_alpha(calculate_lighting(&hit, scene)));
}
