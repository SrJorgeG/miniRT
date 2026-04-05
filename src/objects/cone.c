/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/04/05 19:38:41 by dcid-san         ###   ########.fr       */
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
	return (cone);
}
