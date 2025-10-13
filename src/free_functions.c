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
	if (pl->point)
		free(pl->point);
	if (pl->vector)
		free(pl->vector);
	if (pl->color_range)
		free(pl->color_range);
	free(pl);
}

void	free_cylinder(void *cylinder)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)cylinder;
	if (cy->center)
		free(cy->center);
	if (cy->axys)
		free(cy->axys);
	if (cy->color_range)
		free(cy->color_range);
	free(cy);
}

void	free_sphere(void *sphere)
{
	t_sphere *sp;

	sp = (t_sphere *)sphere;
	if (sp->center)
		free(sp->center);
	if (sp->color_range)
		free(sp->color_range);
	free(sp);
}

/* Aqui creo que podemos reducir lineas ya que ft_stack clear se puede llamar con un stack nulo y no peda con lo que se podria sacar del if
	de momento lo dejo asi porque habra que ir modificando las funciones de liberar.
*/
void	free_map(t_map *map)
{
	if (map->amb_ligt)
	{
		if (map->amb_ligt->amb_col)
			free(map->amb_ligt->amb_col);
		free(map->amb_ligt);
	}
	if (map->camera)
	{
		if (map->camera->view_point)
			free(map->camera->view_point);
		if (map->camera->vector)
			free(map->camera->vector);
		free(map->camera);
	}
	if (map->light)
	{
		if (map->light->light_point)
			free(map->light->light_point);
		if (map->light->color_range)
			free(map->light->color_range);
		free(map->light);
	}
	if (map->planes)
	{
		ft_stack_clear(map->planes, free_plane);
		free(map->planes);
	}
	if (map->spheres)
	{
		ft_stack_clear(map->spheres, free_sphere);
		free(map->spheres);
	}
	if (map->cylinders)
	{
		ft_stack_clear(map->cylinders, free_cylinder);
		free(map->cylinders);
	}
	free(map);
}