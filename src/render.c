/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/06 13:20:57 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_ray get_ray_from_pixel(t_scene *scene, t_vec image_center, t_vec pixel_center)
{
    t_vec x_offset;
    t_vec y_offset;
    t_vec pixel_world;
    t_ray ray;

    x_offset = vector_multiplication(scene->map->camera->right, pixel_center.x);
    y_offset = vector_multiplication(scene->map->camera->up, pixel_center.y);
    pixel_world = vector_sum(*image_center, vector_sum(x_offset, y_offset));
    return ((t_ray) {*scene->map->camera->view_point, vector_normalize(vector_rest(pixel_world, *scene->map->camera->view_point))});
}

int hit_object(t_ray ray, t_object *object, double *obj_distance)
{
	if (object->type == SPHERE)
		return (hit_sphere(t_ray ray, t_object *object, double *obj_distance));

}
}

int	fill_hit_info()
{

}

t_hit get_hits(t_scene *scene, t_ray ray)
{
	t_object	hit_object;
	t_hit		closest;
	double		obj_distance;
	t_list		*current;
	t_object	*obj;

	hit_object = NULL;
	closest.hit = 0;
	closest.t = INFINITY;

 	if (scene->map->last_hit)
    {
        if (hit_object(ray, scene->map->last_hit, &obj_distance))
        {
            if (obj_distance < closest.t)
            {
                fill_hit_info(&closest, t, ray, map->last_hit_obj);
            }
        }
    }
	current = scene->map->objects->first;
	while (current)
	{
		if (hit_object(ray, map->last_hit_obj, &t))
        {
            if (t < closest_hit.t)
            {
                fill_hit_info(&closest_hit, t, ray, map->last_hit_obj);
            }
        }
		current = current->next;
	}
	if (closest.hit)
        scene->map->last_hit = closest.object;

}

t_vec find_pixel_on_viewport(int x, int y, t_scene *scene)
{
    t_real u;
    t_real v;

    u = (x + 0.5) / (t_real)scene->screen_w;
    v = (y + 0.5) / (t_real)scene->screen_h;

    return ((t_vec) {(u - 0.5) * scene->viewport_w , (0.5 - v) * scene->viewport_h, 0});
}

void render(t_scene *scene, mlx_t *mlx, mlx_image_t* img)
{
   	int y = 0;
	int x = 0;
	t_vec pixel_center;
	t_vec image_center;

	image_center = vector_sum(*scene->map->camera->view_point, *scene->map->camera->orientation_nor);
    while (y < scene->screen_h)
	{
		x = 0;
		while (x < scene->screen_w)
		{
            pixel_center = find_pixel_on_viewport(x, y, scene); //Ahora (px, py) son las coordenadas 2D del píxel dentro de la ventana virtual. px va de -viewport_width/2 a +viewport_width/2
            get_hits(scene, get_ray_from_pixel(scene, image_center, pixel_center));
            mlx_put_pixel(img, x, y, pixel_color);
			x++;
		}
		y++;

	}
    if (mlx_image_to_window(mlx, img, 0, 0) < 0)
       	exit_error("Error. mlx_image_to_window\n", NULL);
}
