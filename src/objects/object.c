/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/03/25 00:00:00 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Check if invalid texture creates leaks,
** or call free_object and modify it to check NULL before freeing.
*/
t_object	*create_object(int obj_type, void *object, size_t id, char *args[2])
{
	t_object	*obj;
	int			texture_fd;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->texture_path = NULL;
	obj->texture = NULL;
	if (args[0])
		obj->orientation = create_vector(args[0]);
	if (args[1])
	{
		texture_fd = open(args[1], O_RDONLY);
		if (texture_fd < 0)
			return (free(obj), perror("error in texture_fd"), NULL);
		close(texture_fd);
		obj->texture_path = ft_strdup(args[1]);
	}
	if (!load_texture(obj))
		return (free(obj), NULL);
	obj->object = object;
	obj->type = obj_type;
	obj->id = id;
	return (obj);
}

void	free_object(void *object)
{
	t_object	*obj;

	obj = (t_object *)object;
	if (obj->texture)
		mlx_delete_texture(obj->texture);
	if (obj->texture_path)
		free(obj->texture_path);
	if (obj->type == SPHERE)
		free_sphere(obj->object);
	if (obj->type == CYLINDER)
		free_cylinder(obj->object);
	if (obj->type == PLANE)
		free_plane(obj->object);
	free(obj);
}
