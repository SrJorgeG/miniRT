/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by dcid-san          #+#    #+#             */
/*   Updated: 2025/12/22 20:58:32 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdint.h>
#include <stdlib.h>

void	init_cache(t_scene *scene)
{
	size_t	i;

	i = 0;
	scene->pixel_cache = malloc(scene->map.objects->size * sizeof(t_obj_cache));
	if (!scene->pixel_cache)
		exit_error("Error pixel_cache. malloc\n", NULL);
	while (i < scene->map.objects->size)
	{
		scene->pixel_cache[i].capacity = 1024;
		scene->pixel_cache[i].pixel_count = 0;
		scene->pixel_cache[i].pixels = malloc(scene->pixel_cache[i].capacity
				* sizeof(int) * 2);
		if (!scene->pixel_cache[i].pixels)
			exit_error("Error pixel_cache->pixels. malloc\n", scene);
		i++;
	}
	scene->cache_count = i;
}

int	add_pixel_to_cache(t_obj_cache *cache, int x, int y)
{
	uint32_t	*new_coords;
	uint32_t new_capacity;
	
	if (cache->pixel_count >= cache->capacity)
	{
		new_capacity = cache->capacity * 2;
		printf("cache->capacity: %d", cache->capacity);
		// new_coords = ft_realloc(cache->pixels, cache->capacity,
		//                       sizeof(int) * cache->capacity * 2);
		new_coords = realloc(cache->pixels, (uint32_t)sizeof(uint32_t)
				* new_capacity * 2);
		if (!new_coords)
			return (0);
		cache->pixels = new_coords;
		cache->capacity = new_capacity;
	}
	cache->pixels[cache->pixel_count * 2] = x;
	cache->pixels[(cache->pixel_count * 2) + 1] = y;
	cache->pixel_count++;
	return (1);
}



void clear_cache(t_scene *scene)
{
    int i;
    if (!scene || !scene->pixel_cache)
		return;
	i = 0;
    while (i < scene->cache_count)
	{
        scene->pixel_cache[i].pixel_count = 0;
		i++;
	}
}