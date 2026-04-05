/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec	apply_translation(t_vec point, double tx, double ty, double tz)
{
	point.x += tx;
	point.y += ty;
	point.z += tz;
	return (point);
}

t_vec	apply_rotation_x(t_vec vec, double angle)
{
	t_vec	result;
	double	rad;

	rad = angle * M_PI / 180.0;
	result.x = vec.x;
	result.y = vec.y * cos(rad) - vec.z * sin(rad);
	result.z = vec.y * sin(rad) + vec.z * cos(rad);
	return (result);
}

t_vec	apply_rotation_y(t_vec vec, double angle)
{
	t_vec	result;
	double	rad;

	rad = angle * M_PI / 180.0;
	result.x = vec.x * cos(rad) + vec.z * sin(rad);
	result.y = vec.y;
	result.z = -vec.x * sin(rad) + vec.z * cos(rad);
	return (result);
}

t_vec	apply_rotation_z(t_vec vec, double angle)
{
	t_vec	result;
	double	rad;

	rad = angle * M_PI / 180.0;
	result.x = vec.x * cos(rad) - vec.y * sin(rad);
	result.y = vec.x * sin(rad) + vec.y * cos(rad);
	result.z = vec.z;
	return (result);
}

t_vec	apply_rotations(t_vec vec, double rot_x, double rot_y, double rot_z)
{
	t_vec	result;

	result = apply_rotation_x(vec, rot_x);
	result = apply_rotation_y(result, rot_y);
	result = apply_rotation_z(result, rot_z);
	return (result);
}
