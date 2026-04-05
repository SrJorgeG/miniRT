/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:38:58 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 21:05:08 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	camera_keys(mlx_key_data_t keydata, t_camera *camera)
{
	if (keydata.key == MLX_KEY_UP)
		camera->view_point.y += 5;
	else if (keydata.key == MLX_KEY_DOWN)
		camera->view_point.y -= 5;
	else if (keydata.key == MLX_KEY_RIGHT)
		camera->view_point.x += 5;
	else if (keydata.key == MLX_KEY_LEFT)
		camera->view_point.x -= 5;
	else
		return (0);
	return (1);
}

void	custom_key_hook(mlx_key_data_t keydata, void *param)
{
	t_hook_data	*data;

	data = param;
	if (data->scene->is_rendered)
	{
		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		{
			mlx_close_window(data->mlx);
		}
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		{
			if (move_object(keydata, data) || resize_object(keydata, data)
				|| rotate_object(keydata, data)
				|| camera_keys(keydata, &data->scene->map->camera))
			{
				clear_cache(data->scene);
				render(data->scene, data->mlx, data->image);
				if (data->scene->picked_obj)
					select_object(data->scene, data->scene->picked_obj,
						data->image);
			}
			if (keydata.key == MLX_KEY_Q && data->scene->is_obj_picked)
				deselect_object(data->scene, data->scene->picked_obj,
					data->image);
		}
	}
}
