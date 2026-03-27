/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_object_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:00:00 by dcid-san          #+#    #+#             */
/*   Updated: 2025/03/25 12:00:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	debug_object(t_object *obj)
{
	printf("=== OBJECT id=%lu ===\n", obj->id);
	debug_color("color", obj->color_range);
	if (obj->type == SPHERE)
		debug_sphere((t_sphere *)obj->object);
	else if (obj->type == PLANE)
		debug_plane((t_plane *)obj->object);
	else if (obj->type == CYLINDER)
		debug_cylinder((t_cylinder *)obj->object);
}

void	debug_objects(t_stack *objects)
{
	t_list		*tmp;
	t_object	*obj;

	tmp = objects->first;
	while (tmp)
	{
		obj = (t_object *)tmp->content;
		debug_object(obj);
		tmp = tmp->next;
	}
}
