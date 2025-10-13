/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:34:15 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 17:47:41 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	debug_plane(t_plane *plane)
{
	printf("Plane:\n");
	printf(" Point: (%.2f, %.2f, %.2f)\n", plane->point->x, plane->point->y, plane->point->z);
	printf(" Normal Vector: (%.2f, %.2f, %.2f)\n", plane->vector->x, plane->vector->y, plane->vector->z);
	printf(" Color: (R: %d, G: %d, B: %d)\n", plane->color_range->r, plane->color_range->g, plane->color_range->b);
}
void	debug_sphere(t_sphere *sphere)
{
	printf("Sphere:\n");
	printf(" Center: (%.2f, %.2f, %.2f)\n", sphere->center->x, sphere->center->y, sphere->center->z);
	printf(" Diameter: %.2f\n", sphere->diameter);
	printf(" Color: (R: %d, G: %d, B: %d)\n", sphere->color_range->r, sphere->color_range->g, sphere->color_range->b);
}
void	debug_cylinder(t_cylinder *cylinder)
{
	printf("Cylinder:\n");
	printf(" Center: (%.2f, %.2f, %.2f)\n", cylinder->center->x, cylinder->center->y, cylinder->center->z);
	printf(" Axis: (%.2f, %.2f, %.2f)\n", cylinder->axys->x, cylinder->axys->y, cylinder->axys->z);
	printf(" Diameter: %.2f\n", cylinder->diameter);
	printf(" Height: %.2f\n", cylinder->height);
	printf(" Color: (R: %d, G: %d, B: %d)\n", cylinder->color_range->r, cylinder->color_range->g, cylinder->color_range->b);
}
void	debug_map(t_map *map)
{
	t_list	*current;

	if (map->amb_ligt)
		printf("Ambient Light: Ratio: %.2f, Color: (R: %d, G: %d, B: %d)\n", map->amb_ligt->amb_ratio, map->amb_ligt->amb_col->r, map->amb_ligt->amb_col->g, map->amb_ligt->amb_col->b);
	if (map->camera)
		printf("Camera: View Point: (%.2f, %.2f, %.2f), Vector: (%.2f, %.2f, %.2f), FOV: %ld\n", map->camera->view_point->x, map->camera->view_point->y, map->camera->view_point->z, map->camera->vector->x, map->camera->vector->y, map->camera->vector->z, map->camera->fov);
	
	current = map->planes->first;
	while (current)
	{
		debug_plane((t_plane *)current->content);
		current = current->next;
	}
	current = map->spheres->first;
	while (current)
	{
		debug_sphere((t_sphere *)current->content);
		current = current->next;
	}
	current = map->cylinders->first;
	while (current)
	{
		debug_cylinder((t_cylinder *)current->content);
		current = current->next;
	}
}
