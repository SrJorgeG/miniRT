#include "../../include/minirt.h"

void select_object(t_scene *scene, t_object *object, mlx_image_t *image)
{
	t_obj_cache cache;
	uint32_t i;

	cache = scene->pixel_cache[object->id];
	i = 0;
	while (i < cache.pixel_count)
	{
		mlx_put_pixel(image, cache.pixels[(i * 2)], cache.pixels[(i * 2) + 1], color_to_int_no_alpha((t_color){255,255,255}));
		i++;
	}
    scene->picked_obj = object;
    scene->is_obj_picked = 1;
}

void deselect_object(t_scene *scene, t_object *object, mlx_image_t *image)
{
	t_obj_cache cache;
	uint32_t i;
	t_hit	hit;
	t_vec		pixel_center;
    uint32_t x;
    uint32_t y;

	
	cache = scene->pixel_cache[object->id];
	i = 0;
	while (i < cache.pixel_count)
	{
        x = cache.pixels[i * 2];
        y = cache.pixels[(i * 2) + 1];
        pixel_center = find_pixel_on_viewport(x, y, scene);
	    hit = get_hits(scene, get_ray_from_pixel(scene, scene->image_center,
						pixel_center));
		mlx_put_pixel(image, x, y, color_to_int_no_alpha(calculate_lighting(&hit, scene)));
		i++;
	}
    scene->picked_obj = NULL;
    scene->is_obj_picked = 0;

}

void    make_bigger(t_object *object)
{
    t_sphere *sphere;
    t_cylinder *cylinder;

    if (object->type == SPHERE)
    {
        sphere = object->object;
        sphere->radius += 1;
    }
    if (object->type == CYLINDER)
    {
        cylinder = object->object;
        cylinder->diameter += 1;
    }
    

}
void    make_smaller(t_object *object)
{
    t_sphere *sphere;
    t_cylinder *cylinder;

    if (object->type == SPHERE)
    {
        sphere = object->object;
        sphere->radius -= 1;
    }
    if (object->type == CYLINDER)
    {
        cylinder = object->object;
        cylinder->diameter -= 1;
    }
    

}

int    resize_object(mlx_key_data_t keydata, t_hook_data *data)
{
    t_object *obj;

    obj = data->scene->picked_obj;
    if (!obj)
        return (0);
    if (keydata.key == MLX_KEY_KP_ADD)
        make_bigger(obj);
    else if (keydata.key == MLX_KEY_KP_SUBTRACT)
        make_smaller(obj);
    else
        return(0);
    return(1);

}

void    move_x(t_object *object, double value)
{
    t_sphere    *sphere;
    t_cylinder  *cylinder;
    t_plane     *plane;

    if (object->type == SPHERE)
    {
        sphere = object->object;
        sphere->center.x += value;
    }
    if (object->type == CYLINDER)
    {
        cylinder = object->object;
        cylinder->center.x += value;
    }
    if (object->type == PLANE)
    {
        plane = object->object;
        plane->point.x += value;
    }
    

}
void    move_y(t_object *object, double value)
{
    t_sphere    *sphere;
    t_cylinder  *cylinder;
    t_plane     *plane;

    if (object->type == SPHERE)
    {
        sphere = object->object;
        sphere->center.y += value;
    }
    if (object->type == CYLINDER)
    {
        cylinder = object->object;
        cylinder->center.y += value;
    }
    if (object->type == PLANE)
    {
        plane = object->object;
        plane->point.y += value;
    }
    

}

int    move_object(mlx_key_data_t keydata, t_hook_data *data)
{
    t_object *obj;

    obj = data->scene->picked_obj;
    if (!obj)
        return (0);
    
    if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
        move_x(data->scene->picked_obj, -1);
    else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
        move_x(data->scene->picked_obj, 1);
    else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
        move_y(data->scene->picked_obj, 1);
    else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
        move_y(data->scene->picked_obj, -1);
    else
        return(0);
    return(1);

}
