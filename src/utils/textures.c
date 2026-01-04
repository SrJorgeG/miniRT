#include "../../include/minirt.h"

int   load_texture(t_object *object)
{

    int texture_fd;

    if (object->texture)
        return (1);
    texture_fd = open(object->texture_path, O_RDONLY);
    if (texture_fd < 0)
		return (0);
	close(texture_fd);
    object->texture = mlx_load_png(object->texture_path);
    if (!object->texture)
        return (0);
    return (1);
}

t_color get_texture_color(t_object *object, double u, double v, t_scene *scene)
{
    if (!load_texture(object))
        exit_error("load_texture error\n", scene);
    int x, y, index;
    uint8_t *pixel;
    
    if (! object->texture || !object->texture->pixels)
        return ((t_color){0, 0, 0});
    u = u - floor(u);
    v = v - floor(v);
    x = (int)(u * (object->texture->width - 1));
    y = (int)(v * (object->texture->height - 1));
    if (x < 0)
        x = 0;
    if (x >= (int)object->texture->width)
        x = object->texture->width - 1;
    if (y < 0)
        y = 0;
    if (y >= (int)object->texture->height)
        y = object->texture->height - 1;
    index = (y * object->texture->width + x) * object->texture->bytes_per_pixel;
    pixel = &object->texture->pixels[index];
    
    return ((t_color){pixel[0], pixel[1], pixel[2]});
    
}



void get_sphere_uv(t_vec hit_point, t_vec center, double *u, double *v)
{
    t_vec d;
    double theta, phi;
    
    d = vector_rest(hit_point, center);
    d = vector_normalize(d);
    
    theta = acos(d.y);
    phi = atan2(d.z, d.x);
    
    *u = (phi + M_PI) / (2.0 * M_PI);
    *v = theta / M_PI;
}
t_color textures_handler(t_hit *hit, t_scene *scene)
{
    double u;
    double v;
    if (hit->object->texture_path != NULL)
	{
		if (hit->object->type == SPHERE)
			get_sphere_uv(hit->p, hit->object->center, &u, &v);
		return get_texture_color(hit->object, u, v, scene);
	}
	return (hit->object->color_range);
	
}
// Muestrear color de textura en coordenadas (u,v)
/* t_color sample_texture(mlx_texture_t *tex, double u, double v)
{
    
} */