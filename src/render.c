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

    x_offset = vector_multiplication(scene->map.camera.right, pixel_center.x);
    y_offset = vector_multiplication(scene->map.camera.up, pixel_center.y);
    pixel_world = vector_sum(image_center, vector_sum(x_offset, y_offset));
    return ((t_ray) {scene->map.camera.view_point, vector_normalize(vector_rest(pixel_world, scene->map.camera.view_point))});
}

int hit_object(t_ray ray, t_object *object, double *obj_distance)
{
	if (object->type == SPHERE)
		return (hit_sphere(ray, object->object, obj_distance));
	else if (object->type == CYLINDER)
		return (hit_sphere(ray, object->object, obj_distance));
	else if (object->type == PLANE)
		return (hit_plane(ray, object->object, obj_distance));
	return (0);
}

t_vec	get_hit_normal(t_hit *hit)
{
	t_sphere	*sphere;
	if (hit->object->type == SPHERE)
	{
		sphere = hit->object->object;
		return (vector_normalize(vector_rest(hit->p, sphere->center)));
	}
	return ((t_vec) {0,0,0});

}

void	fill_hit_info(t_hit *closest, double obj_distance, t_object *last_hit)
{
	closest->object = last_hit;
	closest->color = last_hit->color_range;
	closest->t = obj_distance;
	closest->hit = 1;
}

t_hit get_hits(t_scene *scene, t_ray ray)
{
	t_hit		closest;
	double		obj_distance;
	t_list		*current;
	t_object	*obj;

	closest.hit = 0;
	closest.t = INFINITY;

 	if (scene->map.last_hit)
    {
        if (hit_object(ray, scene->map.last_hit, &obj_distance) && obj_distance < closest.t)
        {
            if (obj_distance < closest.t)
                fill_hit_info(&closest, obj_distance, scene->map.last_hit);
        }
    }
	current = scene->map.objects->first;
	while (current)
	{
		obj = current->content;
		if (obj != scene->map.last_hit && hit_object(ray, obj, &obj_distance) && obj_distance < closest.t)
                fill_hit_info(&closest, obj_distance, obj);
		current = current->next;
	}
	if (closest.hit)
	{
		scene->map.last_hit = closest.object;
		closest.p = vector_sum(ray.origin, vector_multiplication(ray.direction, obj_distance));
		closest.normal = get_hit_normal(&closest);
	}
	return (closest);
}

t_vec find_pixel_on_viewport(int x, int y, t_scene *scene)
{
    t_real u;
    t_real v;

    u = (x + 0.5) / (t_real)scene->screen_w;
    v = (y + 0.5) / (t_real)scene->screen_h;

    return ((t_vec) {(u - 0.5) * scene->viewport_w , (0.5 - v) * scene->viewport_h, 0});
}

t_color calculate_lighting(t_hit *hit, t_scene *scene)
{
    t_color final_color;
    t_light *current_light;
    t_list *current;

    // --- PASO 1: Componente Ambiental ---
    // Es el color del objeto afectado por la luz ambiental global.
    // final_color = color_objeto * color_luz_ambiental * ratio_luz_ambiental
    final_color = color_multiply(hit->color, scene->map.amb_ligt.amb_col);
    final_color = color_scale(final_color, scene->map.amb_ligt.amb_ratio);

    current = scene->map.lights->first;
    // --- PASO 2: Iterar sobre todas las luces para la Componente Difusa ---
    while (current)
    {
    	current_light = scene->map.lights->first->content; // Asumo que scene->lights es el inicio de tu lista de luces
        // Vector desde el punto de impacto HACIA la luz
        t_vec light_dir = vector_normalize(vector_rest(current_light->light_point, hit->p));

        // Calcular el factor de luz difusa.
        // Es el producto escalar (coseno del ángulo) entre la normal y la dirección de la luz.
        // El 'dot product' nos dice cuánto "mira" la superficie hacia la luz.
        double diffuse_factor = vector_dot_prod(hit->normal, light_dir);

        // Si el factor es negativo, significa que la luz está detrás de la superficie.
        // En ese caso, no contribuye con luz. Lo clamping a 0.
        if (diffuse_factor < 0)
        {
            diffuse_factor = 0;
        }

        // Calcular el color difuso para ESTA luz
        // color_difuso = color_objeto * color_luz * brillo_luz * factor_difuso
        t_color diffuse_for_this_light;
        diffuse_for_this_light = color_multiply(hit->color, current_light->color_range);
        diffuse_for_this_light = color_scale(diffuse_for_this_light, current_light->brightness * diffuse_factor);

        // Añadir la contribución de esta luz al color final
        final_color = color_add(final_color, diffuse_for_this_light);

        current = current->next; // Avanzar a la siguiente luz
    }

    // --- PASO 3: Clamping ---
    // Asegurarse de que el color final no exceda los límites (ej: 255, 255, 255)
    return (color_clamp(final_color));
}



void render(t_scene *scene, mlx_t *mlx, mlx_image_t* img)
{
   	int y = 0;
	int x = 0;
	t_hit	hit;
	t_vec pixel_center;
	t_vec image_center;

	image_center = vector_sum(scene->map.camera.view_point, scene->map.camera.orientation_nor);
    while (y < scene->screen_h)
	{
		x = 0;
		while (x < scene->screen_w)
		{
            pixel_center = find_pixel_on_viewport(x, y, scene); //Ahora (px, py) son las coordenadas 2D del píxel dentro de la ventana virtual. px va de -viewport_width/2 a +viewport_width/2
            hit = get_hits(scene, get_ray_from_pixel(scene, image_center, pixel_center));
            if (hit.hit)
                mlx_put_pixel(img, x, y, color_to_int_no_alpha(calculate_lighting(&hit, scene)));
            else
                mlx_put_pixel(img, x, y, color_to_int_no_alpha((t_color) {255, 255, 255}));
			x++;
		}
		y++;

	}
    printf("Termino de dibujar la imagen\n");
    if (mlx_image_to_window(mlx, img, 0, 0) < 0)
       	exit_error("Error. mlx_image_to_window\n", NULL);
}
