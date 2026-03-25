/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:07:57 by dcid-san          #+#    #+#             */
/*   Updated: 2025/12/30 13:31:44 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	match_idx(void *lst, void *idx)
{
	t_list		*current;
	t_object	*obj;
	size_t		*value;

	current = lst;
	obj = current->content;
	value = idx;
	if (obj->id == *value)
		return (1);
	else
		return (0);
}

void	object_selector_hook(int32_t x, int32_t y, modifier_key_t mods,
	t_hook_data *data)
{
	t_hit	hit;
	t_vec	pixel_center;
	t_ray	ray;

	(void)mods;
	if (!data->scene->picked_obj)
	{
		pixel_center = find_pixel_on_viewport(x, y, data->scene);
		ray = get_ray_from_pixel(data->scene, data->scene->image_center,
				pixel_center);
		hit = get_hits(data->scene, ray);
		if (hit.hit)
			select_object(data->scene, hit.object, data->image);
	}
	else
	{
		deselect_object(data->scene, data->scene->picked_obj, data->image);
	}
}

void	custom_mouse_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_hook_data	*data;
	int32_t		x;
	int32_t		y;

	data = param;
	if (data->scene->is_rendered)
	{
		if (action == MLX_PRESS && button == MLX_MOUSE_BUTTON_LEFT)
		{
			mlx_get_mouse_pos(data->mlx, &x, &y);
			object_selector_hook(x, y, mods, data);
		}
	}
}
