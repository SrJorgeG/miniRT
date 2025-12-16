/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by dcid-san          #+#    #+#             */
/*   Updated: 2025/12/16 19:38:44 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	init_cache(t_scene *scene)
{
	int32_t	i;

	i = 0;
	scene->pixel_cache = malloc(scene->map.objects->size * sizeof(t_obj_cache));
	while (i < scene->map.objects->size)
	{
		scene->pixel_cache[i].capacity = 1024;
		scene->pixel_cache[i].pixels = malloc(1024 * sizeof(int));
		if (!scene->pixel_cache[i].pixels)
			exit_error("Error. malloc\n", scene);
		scene->pixel_cache[i].pixel_count = 0;
		i++;
	}
}

void	add_pixel_to_cache(t_obj_cache *cache, int x, int y)
{
	int *new_coords;
	int new_capacity;

	if (cache->pixel_count <= cache->capacity)
	{
		ft_realloc(cache->pixels, cache->capacity, cache->capacity * 2);
		cache->capacity = cache->capacity * 2;
	}
}