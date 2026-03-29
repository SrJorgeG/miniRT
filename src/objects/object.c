/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by krusty            #+#    #+#             */
/*   Updated: 2026/03/29 22:51:41 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/*
** Check if invalid texture creates leaks,
** or call free_object and modify it to check NULL before freeing.
*/

void	*set_texture(t_object *obj, char *texture_path)
{
	int			texture_fd;

	texture_fd = open(texture_path, O_RDONLY);
	if (texture_fd < 0)
		return (free(obj), perror("error in texture_fd"), NULL);
	close(texture_fd);
	obj->texture_path = ft_strdup(texture_path);
	if (!obj->texture_path)
		return (free(obj), perror("error in ft_strdup"), NULL);
	return (obj);
}

t_object	*create_object(int obj_type, void *object, size_t id, char *args[2])
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->texture_path = NULL;
	obj->texture = NULL;
	if (args[0])
		obj->orientation = create_vector(args[0]);
	if (args[1])
		if (!set_texture(obj, args[1]))
			return (NULL);
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
	if (obj->type == CONE)
		free_cone(obj->object);
	free(obj);
}
