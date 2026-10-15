/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_preview.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:30:00 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:30:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* Derived cylinder sizes are refreshed once per frame, before the threads
 * start, so the render threads only ever read shared object data. */
void	prepare_objects(t_scene *scene)
{
	t_list		*cur;
	t_object	*obj;
	t_cylinder	*cyl;

	cur = scene->map->objects->first;
	while (cur)
	{
		obj = cur->content;
		if (obj->type == CYLINDER)
		{
			cyl = obj->object;
			cyl->radius = cyl->diameter / 2.0;
			cyl->half_h = cyl->height / 2.0;
		}
		cur = cur->next;
	}
}

void	render(t_scene *scene, mlx_t *mlx, mlx_image_t *img)
{
	render_frame(scene, mlx, img, 1);
}

void	request_preview(t_hook_data *data)
{
	render_frame(data->scene, data->mlx, data->image, PREVIEW_STEP);
	data->scene->needs_full = 1;
	data->scene->last_input = mlx_get_time();
}

void	refine_hook(void *param)
{
	t_hook_data	*data;

	data = param;
	if (!data->scene->needs_full
		|| mlx_get_time() - data->scene->last_input < REFINE_DELAY)
		return ;
	data->scene->needs_full = 0;
	render_frame(data->scene, data->mlx, data->image, 1);
	if (data->scene->picked_obj)
		select_object(data->scene, data->scene->picked_obj, data->image);
}
