/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_sphere	*create_sphere(char **args)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = create_vector(args[1]);
	sphere->diameter = ft_atodbl(args[2]);
	sphere->radius = sphere->diameter / 2;
	if (sphere->diameter <= 0.0)
		return (free_object(sphere), NULL);
	return (sphere);
}
