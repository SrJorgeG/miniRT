/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:00 by dcid-san          #+#    #+#             */
/*   Updated: 2025/03/25 12:00:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	debug_vec(char *name, t_vec v)
{
	printf("%s: (%.4f, %.4f, %.4f)\n", name, v.x, v.y, v.z);
}

void	debug_color(char *name, t_color c)
{
	printf("%s: (%d, %d, %d)\n", name, c.r, c.g, c.b);
}

void	debug_sphere(t_sphere *s)
{
	debug_vec("center", s->center);
	printf("diameter: %.4f\n", s->diameter);
	printf("radius: %.4f\n", s->radius);
}

void	debug_plane(t_plane *p)
{
	debug_vec("point", p->point);
	debug_vec("normal", p->vector);
}

void	debug_cylinder(t_cylinder *c)
{
	debug_vec("center", c->center);
	debug_vec("axis", c->axis);
	printf("diameter: %.4f\n", c->diameter);
	printf("height: %.4f\n", c->height);
}
