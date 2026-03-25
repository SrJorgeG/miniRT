/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_cylinder	*create_cylinder(char **args)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (NULL);
	cylinder->center = create_vector(args[1]);
	cylinder->axis = create_vector(args[2]);
	cylinder->diameter = ft_atodbl(args[3]);
	cylinder->height = ft_atodbl(args[4]);
	if (!is_normalized_vec(cylinder->axis))
		return (perror("Error. Invalid range for cylinder orientation."), NULL);
	if (cylinder->diameter <= 0.0)
		return (perror("Error. Invalid range for cylinder diameter."), NULL);
	if (cylinder->height <= 0.0)
		return (perror("Error. Invalid range for cylinder height."), NULL);
	return (cylinder);
}
