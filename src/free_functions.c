/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:39:18 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/13 15:54:02 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_plane(void	*plane)
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
	t_sphere *sp;

	sp = (t_sphere *)sphere;
	free(sp);
}

/* Aqui creo que podemos reducir lineas ya que ft_stack clear se puede llamar con un stack nulo y no peda con lo que se podria sacar del if
	de momento lo dejo asi porque habra que ir modificando las funciones de liberar.
*/
void	free_map(t_map *map)
{
	if (map->objects)
	{
		ft_stack_clear(map->objects, free_plane);
		free(map->objects);
	}
	free(map);
}

void	free_scene(t_scene *scene)
{
	free_map(&scene->map);
	free(scene);
}