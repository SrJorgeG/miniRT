/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:05:17 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/15 13:20:57 by dcid-san         ###   ########.fr       */
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
	map->lights = ft_stack_new();
	map->objects = ft_stack_new();
	if (!map->objects)
		exit_error("Error. malloc. \n", map);
	return (map);
}
