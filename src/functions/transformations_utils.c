/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec	transform_point(t_vec point, double rot_x, double rot_y,
		double rot_z, double tx, double ty, double tz)
{
	t_vec	result;

	result = apply_rotations(point, rot_x, rot_y, rot_z);
	result = apply_translation(result, tx, ty, tz);
	return (result);
}

t_vec	transform_normal(t_vec normal, double rot_x, double rot_y, double rot_z)
{
	t_vec	result;

	result = apply_rotations(normal, rot_x, rot_y, rot_z);
	return (vector_normalize(result));
}
