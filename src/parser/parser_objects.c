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

static void	add_obj_node(t_scene *scene, t_object *obj)
{
	t_list	*node;

	node = ft_lstnew(obj);
	if (!node)
		exit_error("Error. malloc\n", scene);
	ft_stack_add_back(scene->map.objects, node);
}

void	parse_sphere(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_sphere	*sphere;

	if (ft_strlst_len(args) != 4 && (has_texture
		&& ft_strlst_len(args) != 6))
		exit_error("Error. Invalid map data, incompleted sphere row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_strisdbl(args[2])
		|| !ft_str_is_color(args[3])
		|| (has_texture && !ft_str_is_vector(args[4])))
		exit_error("Error invalid map data, wrong data in sphere row [].\n",
			scene);
	sphere = create_sphere(args);
	if (!sphere)
		exit_error("Error create_sphere:\n", scene);
	if (has_texture)
		obj = create_object(SPHERE, sphere, scene->map.objects->size,
			(char *[2]){args[4], args[5]});
	else
		obj = create_object(SPHERE, sphere, scene->map.objects->size,
			(char *[2]){NULL, NULL});
	if (!obj)
		return (free(sphere), exit_error("Error.create_object malloc\n",
			scene));
	if (!create_color(args[3], &obj->color_range))
		exit_error("Error. Sphere color_range: ", scene);
	add_obj_node(scene, obj);
}

void	parse_plane(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_plane		*plane;

	if (ft_strlst_len(args) != 4 && (has_texture && ft_strlst_len(args) != 5))
		exit_error("Error. Invalid map data, incompleted plane row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2])
		|| !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in plane row.\n", scene);
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
		exit_error("Error. Invalid range for plane orientation.", scene);
	add_obj_node(scene, obj);
}

void	parse_cylinder(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_cylinder	*cylinder;

	if (ft_strlst_len(args) != 6 && (has_texture && ft_strlst_len(args) != 7))
		exit_error("Error. Invalid map data, incompleted cylinder row.\n",
			scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2])
		|| (!ft_strisdbl(args[3])) || (!ft_strisdbl(args[4]))
		|| (!ft_str_is_color(args[5])))
		exit_error("Error invalid map data, wrong data in cylinder row.\n",
			scene);
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
	add_obj_node(scene, obj);
}
