/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 20:52:11 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_map(t_scene *scene)
{
	scene->map = malloc(sizeof(t_map));
	if (!scene->map)
		exit_error("Error init_map. malloc. \n", scene);
	scene->map->has_amb_ligt = 0;
	scene->map->has_camera = 0;
	scene->map->has_lights = 0;
	scene->map->lights = ft_stack_new();
	scene->map->objects = ft_stack_new();
	if (!scene->map->objects)
		exit_error("Error init_map. malloc. \n", scene);
}