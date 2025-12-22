#include "../../include/minirt.h"

void	debug_vec(char *name, t_vec v)
{
	printf("%s: (%.4f, %.4f, %.4f)\n", name, v.x, v.y, v.z);
}

void	debug_color(char *name, t_color c)
{
	printf("%s: (%d, %d, %d)\n", name, c.r, c.g, c.b);
}

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

void	debug_sphere(t_sphere *s)
{
	debug_vec("center", s->center);
	printf("diameter: %.4f\n", s->diameter);
	printf("radius: %.4f\n", s->radius);
}

void	debug_plane(t_plane *p)
{
	debug_vec("point", p->point);
	debug_vec("normal", p->vector);
}

void	debug_cylinder(t_cylinder *c)
{
	debug_vec("center", c->center);
	debug_vec("axis", c->axys);
	printf("diameter: %.4f\n", c->diameter);
	printf("height: %.4f\n", c->height);
}

void	debug_object(t_object *obj)
{
	printf("=== OBJECT id=%d ===\n", obj->id);
	debug_color("color", obj->color_range);
	if (obj->type == SPHERE)
		debug_sphere((t_sphere *)obj->object);
	else if (obj->type == PLANE)
		debug_plane((t_plane *)obj->object);
	else if (obj->type == CYLINDER)
		debug_cylinder((t_cylinder *)obj->object);
}

void	debug_objects(t_stack *objects)
{
	t_list		*tmp;
	t_object	*obj;

	tmp = objects->first;
	while (tmp)
	{
		obj = (t_object *)tmp->content;
		debug_object(obj);
		tmp = tmp->next;
	}
}

void	debug_lights(t_stack *lights)
{
	t_list	*tmp;
	t_light	*obj;

	tmp = lights->first;
	while (tmp)
	{
		obj = (t_light *)tmp->content;
		debug_light(obj);
		tmp = tmp->next;
	}
}

void	debug_map(t_map *map)
{
	printf("\n======= MAP DEBUG =======\n");
	printf("has_camera: %d\n", map->has_camera);
	printf("has_ambient: %d\n", map->has_amb_ligt);
	printf("has_lights: %d\n", map->has_lights);
	if (map->has_camera)
		debug_camera(&map->camera);
	if (map->has_amb_ligt)
		debug_ambient(&map->amb_ligt);
	if (map->has_lights)
		debug_lights(map->lights);
	debug_objects(map->objects);
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
	debug_map(&scene->map);
}
