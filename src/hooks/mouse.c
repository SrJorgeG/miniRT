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

int	match_idx(t_list *lst, int *idx)
{
	t_object *obj;
	obj = lst->content;
	if (obj->id == *idx)
	{
		/* code */
	}
	
}

void	object_selector_hook(mlx_key_data_t keydata, t_hook_data *data)
{
	t_hit	click_info;
	
	int32_t	x;
	int32_t	y;
	size_t	index;
	int		*pixel;

	if (!data->scene->is_rendered)
		return;
	if (keydata.key == MLX_MOUSE_BUTTON_LEFT)
	{
		mlx_get_mouse_pos(data->mlx, &click_info.p.x, &click_info.p.y);
		 // 2. LEER PICKING BUFFER
		int index = (click_info.p.y * data->scene->screen_w + click_info.p.x) * 4;
		pixel = &data->scene->pixel_cache->pixels[index];
		
		// 3. DECODIFICAR ID
		index = (pixel[0] << 16) | (pixel[1] << 8) | pixel[2];
		click_info.object = ft_lstfind_cmp(data->scene->map.objects->first, &index, match_idx);
		
		printf("Click en (%d, %d) → object_id=%d\n", click_info.p.x, click_info.p.y, index);
	}
	
}
