/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by dcid-san          #+#    #+#             */
/*   Updated: 2025/12/16 17:47:33 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_cache(t_scene *scene)
{
	int32_t i;

	i = 0;
	scene->pixel_cache = malloc(scene->map.objects->size * sizeof(t_obj_cache));

	while (i < scene->map.objects->size)
	{
		i++;
	}
}