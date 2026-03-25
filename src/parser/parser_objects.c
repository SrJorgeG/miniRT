/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by krusty            #+#    #+#             */
/*   Updated: 2025/12/22 20:58:32 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse_sphere(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_sphere	*sphere;
	t_list		*node;

	sphere = create_sphere(args);
	if (!sphere)
		exit_error("Error create_sphere:\n", scene);
	if (has_texture)
		obj = create_object(SPHERE, sphere, scene->map.objects->size,
				(char *[2]){args[4], args[5]});
	if (!has_texture)
		obj = create_object(SPHERE, sphere, scene->map.objects->size,
				(char *[2]){NULL, NULL});
	if (!obj)
		return (free(sphere), exit_error("Error.create_object malloc\n",
				scene));
	if (!create_color(args[3], &obj->color_range))
		exit_error("Error. Sphere color_range: ", scene);
	node = ft_lstnew(obj);
	if (!node)
	{
		free_object(obj);
		exit_error("Error. malloc\n", scene);
	}
	ft_stack_add_back(scene->map.objects, node);
}

void	parse_plane(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_plane		*plane;
	t_list		*node;

	plane = create_plane(args);
	if (!plane)
		exit_error("Error parse_plane. malloc\n", scene);
	if (has_texture)
		obj = create_object(PLANE, plane, scene->map.objects->size,
				(char *[2]){args[2], args[4]});
	else
		obj = create_object(PLANE, plane, scene->map.objects->size,
				(char *[2]){NULL, NULL});
	if (!obj)
		return (free_plane(plane), exit_error(
				"Error parse_plane. create_object\n", scene));
	if (!create_color(args[3], &obj->color_range))
		exit_error("Error. Plane color_range: ", scene);
	if (!is_normalized_vec(plane->vector))
		exit_error("Error. Plane orientation invalid.\n", scene);
	node = ft_lstnew(obj);
	if (!node)
		return (free_object(obj),
			exit_error("Error. malloc\n", scene));
	ft_stack_add_back(scene->map.objects, node);
}

void	parse_cylinder(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_cylinder	*cylinder;
	t_list		*node;

	cylinder = create_cylinder(args);
	if (!cylinder)
		exit_error("Error parse_cylinder: ", scene);
	if (has_texture)
		obj = create_object(CYLINDER, cylinder, scene->map.objects->size,
				(char *[2]){args[2], args[6]});
	else
		obj = create_object(CYLINDER, cylinder, scene->map.objects->size,
				(char *[2]){args[2], NULL});
	if (!obj)
		return (free_cylinder(cylinder),
			exit_error("Error parse_cylinder: ", scene));
	if (!create_color(args[5], &obj->color_range))
		exit_error("Error. Cylinder color_range: ", scene);
	node = ft_lstnew(obj);
	if (!node)
		return (free_object(obj),
			exit_error("Error. malloc\n", scene));
	ft_stack_add_back(scene->map.objects, node);
}
