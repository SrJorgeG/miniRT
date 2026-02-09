#include "../../include/minirt.h"

int   load_texture(t_object *object)
{

    int texture_fd;

    if (!object->texture_path)
		return (1);
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

// Rotar vector al sistema de coordenadas definido por la orientación

t_vec rotate_to_texture_space(t_vec d, t_vec orientation)
{
    t_vec up, right, forward;
    t_vec result;
    
    // La orientación define el "norte" de la textura
    up = vector_normalize(orientation);
    
    // Crear sistema de coordenadas local
    // Right:  perpendicular a up
    if (fabs(up.y) > 0.9)
        right = vector_normalize(vector_cross_prod(up, (t_vec){1, 0, 0}));
    else
        right = vector_normalize(vector_cross_prod(up, (t_vec){0, 1, 0}));
    
    // Forward:  perpendicular a up y right
    forward = vector_cross_prod(up, right);
    
    // Proyectar d en el sistema local
    result. x = vector_dot_prod(d, right);
    result.y = vector_dot_prod(d, up);
    result.z = vector_dot_prod(d, forward);
    
    return (result);
}

void get_sphere_uv(t_vec hit_point, t_object *object, double *u, double *v)
{
	t_sphere	*sphere;
    t_vec d;
    double theta, phi;
    
	sphere = (t_sphere *) object->object;
    d = vector_rest(hit_point, sphere->center);
    d = vector_normalize(d);
    d = rotate_to_texture_space(d, object->orientation);
    theta = acos(d.y);
    phi = atan2(d.z, d.x);
    
    *u = (phi + M_PI) / (2.0 * M_PI);
    *v = theta / M_PI;
}

// quizas la escala convenga ponerla como parametro??????
void get_plane_uv(t_vec hit_point, t_object *object, double *u, double *v)
{
    t_plane *plane;
    t_vec local_hit;
    t_vec right, forward;
    double scale;
    
    plane = (t_plane *)object->object;
    t_vec up = vector_normalize(plane->vector);
    if (fabs(up.y) > 0.9)
        right = vector_normalize(vector_cross_prod(up, (t_vec){1, 0, 0}));
    else
        right = vector_normalize(vector_cross_prod(up, (t_vec){0, 1, 0}));
    
    forward = vector_cross_prod(up, right);
    if (object->orientation. x != 0 || object->orientation.y != 0 || object->orientation.z != 0)
    {
        right = rotate_to_texture_space(right, object->orientation);
        forward = rotate_to_texture_space(forward, object->orientation);
    }
    local_hit = vector_rest(hit_point, plane->point);
    
    scale = 0.1;
    
    *u = vector_dot_prod(local_hit, right) * scale;
    *v = vector_dot_prod(local_hit, forward) * scale;
    
    *u = *u - floor(*u);
    *v = *v - floor(*v);
}

/* d es el vector desde el centro del cilindro al punto de impacto, el resto es intuitivo */
void get_cylinder_uv(t_vec hit_point, t_object *object, double *u, double *v)
{
    t_cylinder *cylinder;
    t_vec d, axis;
    t_vec projection, radial;
    double height, phi;
    double cyl_height;
    
    cylinder = (t_cylinder *)object->object;
    axis = vector_normalize(object->orientation);
    d = vector_rest(hit_point, cylinder->center);
    height = vector_dot_prod(d, axis);
    
    projection = vector_scale(axis, height);
    radial = vector_rest(d, projection);
    radial = vector_normalize(radial);
    
    if (object->orientation. x != 0 || object->orientation.y != 0 || object->orientation.z != 0)
        radial = rotate_to_texture_space(radial, object->orientation);    
    phi = atan2(radial.z, radial.x);
    *u = (phi + M_PI) / (2.0 * M_PI);
    
    cyl_height = cylinder->height;
    *v = (height + cyl_height / 2.0) / cyl_height;
    if (*v < 0.0) *v = 0.0;
    if (*v > 1.0) *v = 1.0;
}

t_color textures_handler(t_hit *hit, t_scene *scene)
{
    double u;
    double v;
    if (hit->object->texture_path != NULL)
	{
		if (hit->object->type == SPHERE)
			get_sphere_uv(hit->p, hit->object, &u, &v);
		if (hit->object->type == CYLINDER)
			get_cylinder_uv(hit->p, hit->object, &u, &v);
		if (hit->object->type == PLANE)
			get_plane_uv(hit->p, hit->object, &u, &v);
		return get_texture_color(hit->object, u, v, scene);
	}
	return (hit->object->color_range);
	
}
// Muestrear color de textura en coordenadas (u,v)
/* t_color sample_texture(mlx_texture_t *tex, double u, double v)
{
    
} */