/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by dcid-san          #+#    #+#             */
/*   Updated: 2025/12/16 20:38:25 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include "../../include/minirt.h"

void init_cache(t_scene *scene)
{
	size_t i;

	i = 0;
	scene->pixel_cache = malloc(scene->map.objects->size * sizeof(t_obj_cache));
	if (!scene->pixel_cache)
		exit_error("Error. malloc\n", NULL);
	while (i < scene->map.objects->size)
	{
		scene->pixel_cache[i].capacity = 1024;
		scene->pixel_cache[i].pixels = malloc(1024 * sizeof(int) * 2);
		if (!scene->pixel_cache[i].pixels)
			exit_error("Error. malloc\n", scene);
		scene->pixel_cache[i].pixel_count = 0;
		i++;
	}
}

int add_pixel_to_cache(t_obj_cache *cache, int x, int y)
{
	int *new_coords;

	if (cache->pixel_count >= cache->capacity)
	{
		cache->capacity *= 2;

		printf("cache->capacity: %d", cache->capacity);
		// new_coords = ft_realloc(cache->pixels, cache->capacity,
		//                       sizeof(int) * cache->capacity * 2);
		new_coords = realloc(cache->pixels,
		                     (uint32_t) sizeof(int) * cache->capacity * 2);
		if (!new_coords)
			return (0);
		cache->pixels = new_coords;
	}
	cache->pixels[cache->pixel_count * 2] = x;
	cache->pixels[(cache->pixel_count * 2) + 1] = y;
	cache->pixel_count++;
	return (1);
}
