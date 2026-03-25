/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:39:18 by dcid-san          #+#    #+#             */
/*   Updated: 2026/01/04 16:15:35 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_plane(void *plane)
{
	t_plane	*pl;

	pl = (t_plane *)plane;
	free(pl);
}

void	free_cylinder(void *cylinder)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)cylinder;
	free(cy);
}

void	free_sphere(void *sphere)
{
	t_sphere	*sp;

	sp = (t_sphere *)sphere;
	free(sp);
}

void	free_map(t_map *map)
{
	if (map->objects)
	{
		ft_stack_clear(map->objects, free_object);
		free(map->objects);
	}
	free(map);
}

void	free_cache(t_scene *scene)
{
	int	i;

	if (!scene || !scene->pixel_cache)
		return ;
	i = 0;
	while (i < scene->cache_count)
	{
		free(scene->pixel_cache[i].pixels);
		scene->pixel_cache[i].pixels = NULL;
		i++;
	}
	free(scene->pixel_cache);
	scene->pixel_cache = NULL;
	scene->cache_count = 0;
}
