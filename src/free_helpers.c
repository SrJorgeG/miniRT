/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:35:00 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 21:28:46 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_light(void *l)
{
	t_light *light;
	
	if (l)
	{
		light = (t_light *)l;
		free(light);
	}
}

void	free_plane(void *plane)
{
	t_plane	*pl;

	if (plane)
	{
		pl = (t_plane *)plane;
		free(pl);
	}
	
}

void	free_cylinder(void *cylinder)
{
	t_cylinder	*cy;

	if (cylinder)
	{
		cy = (t_cylinder *)cylinder;
		free(cy);
	}
	
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
	if (map->lights)
	{
		ft_stack_clear(map->lights, free_light);
		free(map->lights);
	}
	
	free(map);
}

