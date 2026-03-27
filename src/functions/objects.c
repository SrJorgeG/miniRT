/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:00 by dcid-san          #+#    #+#             */
/*   Updated: 2025/03/25 12:00:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	select_object(t_scene *scene, t_object *object, mlx_image_t *image)
{
	t_obj_cache	cache;
	uint32_t	i;

	cache = scene->pixel_cache[object->id];
	i = 0;
	while (i < cache.pixel_count)
	{
		brighten_pixel(image, cache.pixels[(i * 2)], cache.pixels[(i * 2) + 1]);
		i++;
	}
	scene->picked_obj = object;
	scene->is_obj_picked = 1;
}

void	deselect_object(t_scene *scene, t_object *object, mlx_image_t *image)
{
	t_obj_cache	cache;
	uint32_t	i;

	cache = scene->pixel_cache[object->id];
	i = 0;
	while (i < cache.pixel_count)
	{
		restore_pixel(scene, image, cache.pixels[i * 2],
			cache.pixels[(i * 2) + 1]);
		i++;
	}
	scene->picked_obj = NULL;
	scene->is_obj_picked = 0;
}

int	resize_object(mlx_key_data_t keydata, t_hook_data *data)
{
	t_object	*obj;

	obj = data->scene->picked_obj;
	if (!obj)
		return (0);
	if (keydata.key == MLX_KEY_KP_ADD)
		resize_helper(obj, 1);
	else if (keydata.key == MLX_KEY_KP_SUBTRACT)
		resize_helper(obj, 0);
	else
		return (0);
	return (1);
}

int	move_object(mlx_key_data_t keydata, t_hook_data *data)
{
	t_object	*obj;

	obj = data->scene->picked_obj;
	if (!obj || keydata.modifier)
		return (0);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
		move_helper(obj, -1, 0);
	else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
		move_helper(obj, 1, 0);
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
		move_helper(obj, 0, 1);
	else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
		move_helper(obj, 0, -1);
	else
		return (0);
	return (1);
}

int	rotate_object(mlx_key_data_t keydata, t_hook_data *data)
{
	t_object	*obj;

	obj = data->scene->picked_obj;
	if (!obj)
		return (0);
	if (keydata.modifier == MLX_CONTROL && keydata.key == MLX_KEY_LEFT)
		obj->orientation.x -= 0.1;
	else if (keydata.modifier == MLX_CONTROL && keydata.key == MLX_KEY_RIGHT)
		obj->orientation.x += 0.1;
	else if (keydata.modifier == MLX_CONTROL && keydata.key == MLX_KEY_UP)
		obj->orientation.y += 0.1;
	else if (keydata.modifier == MLX_CONTROL && keydata.key == MLX_KEY_DOWN)
		obj->orientation.y -= 0.1;
	else if (keydata.modifier == MLX_CONTROL && keydata.key == MLX_KEY_W)
		obj->orientation.z += 0.1;
	else if (keydata.modifier == MLX_CONTROL && keydata.key == MLX_KEY_S)
		obj->orientation.z -= 0.1;
	else
		return (0);
	clamp_orientation(&obj->orientation);
	obj->orientation = vector_normalize(obj->orientation);
	return (1);
}
