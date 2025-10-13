/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/13 15:42:33 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/* 
	-PENDIENTE LIBERAR BIEN LOS MALLOC, SE LE PASARÁ PROBABLEMENTE UN T_DATA GENERAL A EXIT_ERROR Y SE LIBERARÁ TODO LO ALOCADO AHÍ.
*/
t_map	*init_map()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		exit_error("Error. malloc. \n", NULL);
	map->amb_ligt = NULL;
	map->camera = NULL;
	map->light = NULL;
	map->cylinders = ft_stack_new();
	if (!map->cylinders)
		exit_error("Error. malloc. \n", NULL);
	map->spheres = ft_stack_new();
	if (!map->spheres)
		exit_error("Error. malloc. \n", NULL);
	map->planes = ft_stack_new();
	if (!map->planes)
		exit_error("Error. malloc. \n", NULL);
	return (map);
}
