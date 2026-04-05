/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_cone	*create_cone(char **args)
{
	t_cone	*cone;

	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->top = create_vector(args[1]);
	cone->axis = create_vector(args[2]);
	cone->diameter = ft_atodbl(args[3]);
	cone->height = ft_atodbl(args[4]);
	if (!is_normalized_vec(cone->axis))
		return (perror("Error. Invalid range for cone orientation."), NULL);
	if (cone->diameter <= 0.0)
		return (perror("Error. Invalid range for cone diameter."), NULL);
	if (cone->height <= 0.0)
		return (perror("Error. Invalid range for cone height."), NULL);
	cone->rot_x = 0.0;
	cone->rot_y = 0.0;
	cone->rot_z = 0.0;
	cone->trans_x = 0.0;
	cone->trans_y = 0.0;
	cone->trans_z = 0.0;
	return (cone);
}
