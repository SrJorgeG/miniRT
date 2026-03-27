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
	int	fd;

	if (!object->texture_path || object->texture)
		return (1);
	fd = open(object->texture_path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	object->texture = mlx_load_png(object->texture_path);
	return (object->texture != NULL);
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
	else if (x >= (int)object->texture->width)
		x = object->texture->width - 1;
	if (y < 0)
		y = 0;
	else if (y >= (int)object->texture->height)
		y = object->texture->height - 1;
	index = (y * object->texture->width + x)
		* object->texture->bytes_per_pixel;
	pixel = &object->texture->pixels[index];
	return ((t_color){pixel[0], pixel[1], pixel[2]});
}

void	get_object_uv(t_vec hit, t_object *obj, double *u, double *v)
{
	t_vec	d;

	d = vector_rest(hit, ((t_sphere *)obj->object)->center);
	if (obj->type == SPHERE)
	{
		d = vector_normalize(d);
		*u = (atan2(d.z, d.x) + M_PI) / (2.0 * M_PI);
		*v = acos(d.y) / M_PI;
	}
	else if (obj->type == CYLINDER)
	{
		*u = (atan2(d.z, d.x) + M_PI) / (2.0 * M_PI);
		*v = 0.5;
	}
	else if (obj->type == PLANE)
	{
		*u = d.x * 0.1 - floor(d.x * 0.1);
		*v = d.z * 0.1 - floor(d.z * 0.1);
	}
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
