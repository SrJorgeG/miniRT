/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2026/01/05 16:07:06 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

static void	render_pixel_row(t_scene *scene, mlx_image_t *img, int y)
{
	int		x;
	t_hit	hit;
	t_ray	ray;
	t_vec	pixel_center;

	x = 0;
	while (x < scene->screen_w)
	{
		pixel_center = find_pixel_on_viewport(x, y, scene);
		ray = get_ray_from_pixel(scene, scene->image_center, pixel_center);
		hit = get_hits(scene, ray);
		if (hit.hit)
			mlx_put_pixel(img, x, y,
				color_to_int_no_alpha(calculate_lighting(&hit, scene)));
		else
			mlx_put_pixel(img, x, y,
				color_to_int_no_alpha((t_color){0, 0, 0}));
		if (hit.hit)
			add_pixel_to_cache(&scene->pixel_cache[hit.object->id], x, y);
		x++;
	}
}

static void	render_scanlines(t_scene *scene, mlx_image_t *img)
{
	int	y;

	y = 0;
	while (y < scene->screen_h)
	{
		render_pixel_row(scene, img, y);
		y++;
	}
}

void	render(t_scene *scene, mlx_t *mlx, mlx_image_t *img)
{
	t_vec	orientation_normal;

	scene->is_rendered = 0;
	orientation_normal = scene->map.camera.orientation_nor;
	scene->image_center = vector_sum(scene->map.camera.view_point,
			orientation_normal);
	render_scanlines(scene, img);
	printf("Termino de dibujar la imagen\n");
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		exit_error("Error. mlx_image_to_window\n", NULL);
	scene->is_rendered = 1;
}
