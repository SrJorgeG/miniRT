/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:49 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	load_texture(t_object *object)
{
	int	texture_fd;

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

t_color	get_texture_color(t_object *object, double u, double v, t_scene *scene)
{
	int		x;
	int		y;
	int		index;
	uint8_t	*pixel;

	if (!load_texture(object))
		exit_error("load_texture error\n", scene);
	if (!object->texture || !object->texture->pixels)
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
	index = (y * object->texture->width + x)
		* object->texture->bytes_per_pixel;
	pixel = &object->texture->pixels[index];
	return ((t_color){pixel[0], pixel[1], pixel[2]});
}

static void	get_sphere_uv_helper(t_vec d, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(d.y);
	phi = atan2(d.z, d.x);
	*u = (phi + M_PI) / (2.0 * M_PI);
	*v = theta / M_PI;
}

static void	get_plane_uv_helper(t_plane *plane, t_object *obj, t_vec hit_point,
		double *u, double *v)
{
	t_vec	right;
	t_vec	forward;
	t_vec	local_hit;

	right = vector_normalize(plane->vector);
	if (fabs(right.y) < 0.9)
		forward = vector_normalize(vector_cross_prod(right, (t_vec){0, 1, 0}));
	else
		forward = vector_normalize(vector_cross_prod(right, (t_vec){1, 0, 0}));
	local_hit = vector_rest(hit_point, plane->point);
	*u = vector_dot_prod(local_hit, forward) * 0.1;
	*v = vector_dot_prod(local_hit, right) * 0.1;
	*u = *u - floor(*u);
	*v = *v - floor(*v);
}

static void	get_cylinder_uv_helper(t_cylinder *cyl, t_object *obj,
		t_vec hit_point, double *u, double *v)
{
	t_vec	axis;
	t_vec	d;
	double	height;

	axis = vector_normalize(obj->orientation);
	d = vector_rest(hit_point, cyl->center);
	height = vector_dot_prod(d, axis);
	d = vector_rest(d, vector_scale(axis, height));
	d = vector_normalize(d);
	*u = (atan2(d.z, d.x) + M_PI) / (2.0 * M_PI);
	*v = (height + cyl->height / 2.0) / cyl->height;
	if (*v < 0.0)
		*v = 0.0;
	if (*v > 1.0)
		*v = 1.0;
}

void	get_object_uv(t_vec hit_point, t_object *object, double *u, double *v)
{
	t_sphere	*sphere;
	t_vec		d;

	if (object->type == SPHERE)
	{
		sphere = (t_sphere *)object->object;
		d = vector_rest(hit_point, sphere->center);
		d = vector_normalize(d);
		get_sphere_uv_helper(d, u, v);
	}
	else if (object->type == CYLINDER)
		get_cylinder_uv_helper((t_cylinder *)object->object, object,
			hit_point, u, v);
	else if (object->type == PLANE)
		get_plane_uv_helper((t_plane *)object->object, object, hit_point, u, v);
}

t_color	textures_handler(t_hit *hit, t_scene *scene)
{
	double	u;
	double	v;

	u = 0;
	v = 0;
	if (hit->object->texture_path != NULL)
	{
		get_object_uv(hit->p, hit->object, &u, &v);
		return (get_texture_color(hit->object, u, v, scene));
	}
	return (hit->object->color_range);
}
