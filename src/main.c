/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:39:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/13 15:50:25 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main(int ac, char *av[])
{
	t_map *map;
	
	if(ac != 2)
		exit_error("Error, invalid number of arguments\n", NULL);
	
	map = parser(av[1]);
	debug_map(map);
	free_map(map);
	/* 
		- CARGAR MINILIBX -> Ventanas, imagen, poder dibujar algo, hooks.
		- Setear la camara.
		- Calcular ajustes de renderizado 
		- C
	*/	
}
