/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by krusty            #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	parse_sphere_translation(t_sphere *sphere, char **args,
		int args_count)
{
	t_vec	trans;

	if (args_count < 5)
	{
		sphere->trans_x = 0.0;
		sphere->trans_y = 0.0;
		sphere->trans_z = 0.0;
		return ;
	}
	if (!ft_str_is_vector(args[4]))
	{
		sphere->trans_x = 0.0;
		sphere->trans_y = 0.0;
		sphere->trans_z = 0.0;
		return ;
	}
	trans = create_vector(args[4]);
	sphere->trans_x = trans.x;
	sphere->trans_y = trans.y;
	sphere->trans_z = trans.z;
}

void	parse_sphere(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_sphere	*sphere;
	t_list		*node;
	int			args_count;

	args_count = ft_strlst_len(args);
	sphere = create_sphere(args);
	if (!sphere)
		exit_error("Error create_sphere:\n", scene);
	parse_sphere_translation(sphere, args, args_count);
	if (has_texture)
		obj = create_object(SPHERE, sphere, scene->map->objects->size,
				(char *[2]){args[4], args[5]});
	if (!has_texture)
		obj = create_object(SPHERE, sphere, scene->map->objects->size,
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
	ft_stack_add_back(scene->map->objects, node);
}

static void	parse_plane_rotations(t_plane *plane, char **args, int args_count)
{
	if (args_count < 5)
	{
		plane->rot_x = 0.0;
		plane->rot_y = 0.0;
		plane->rot_z = 0.0;
		return ;
	}
	if (!ft_strisdbl(args[4]))
	{
		plane->rot_x = 0.0;
		plane->rot_y = 0.0;
		plane->rot_z = 0.0;
		return ;
	}
	plane->rot_x = ft_atodbl(args[4]);
	if (args_count > 5 && ft_strisdbl(args[5]))
		plane->rot_y = ft_atodbl(args[5]);
	else
		plane->rot_y = 0.0;
	if (args_count > 6 && ft_strisdbl(args[6]))
		plane->rot_z = ft_atodbl(args[6]);
	else
		plane->rot_z = 0.0;
}

static void	parse_plane_translation(t_plane *plane, char **args,
		int args_count)
{
	t_vec	trans;
	int		trans_idx;

	trans_idx = 4;
	if (args_count > 4 && ft_strisdbl(args[4]))
		trans_idx = 7;
	else
		trans_idx = 4;
	if (args_count < trans_idx + 1)
	{
		plane->trans_x = 0.0;
		plane->trans_y = 0.0;
		plane->trans_z = 0.0;
		return ;
	}
	if (!ft_str_is_vector(args[trans_idx]))
	{
		plane->trans_x = 0.0;
		plane->trans_y = 0.0;
		plane->trans_z = 0.0;
		return ;
	}
	trans = create_vector(args[trans_idx]);
	plane->trans_x = trans.x;
	plane->trans_y = trans.y;
	plane->trans_z = trans.z;
}

void	parse_plane(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_plane		*plane;
	t_list		*node;
	int			args_count;

	args_count = ft_strlst_len(args);
	plane = create_plane(args);
	if (!plane)
		exit_error("Error parse_plane. malloc\n", scene);
	parse_plane_rotations(plane, args, args_count);
	parse_plane_translation(plane, args, args_count);
	if (has_texture)
		obj = create_object(PLANE, plane, scene->map->objects->size,
				(char *[2]){args[2], args[4]});
	else
		obj = create_object(PLANE, plane, scene->map->objects->size,
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
	ft_stack_add_back(scene->map->objects, node);
}

static void	parse_cylinder_rotations(t_cylinder *cylinder, char **args,
		int args_count)
{
	if (args_count < 7)
	{
		cylinder->rot_x = 0.0;
		cylinder->rot_y = 0.0;
		cylinder->rot_z = 0.0;
		return ;
	}
	if (!ft_strisdbl(args[6]))
	{
		cylinder->rot_x = 0.0;
		cylinder->rot_y = 0.0;
		cylinder->rot_z = 0.0;
		return ;
	}
	cylinder->rot_x = ft_atodbl(args[6]);
	if (args_count > 7 && ft_strisdbl(args[7]))
		cylinder->rot_y = ft_atodbl(args[7]);
	else
		cylinder->rot_y = 0.0;
	if (args_count > 8 && ft_strisdbl(args[8]))
		cylinder->rot_z = ft_atodbl(args[8]);
	else
		cylinder->rot_z = 0.0;
}

static void	parse_cylinder_translation(t_cylinder *cylinder, char **args,
		int args_count)
{
	t_vec	trans;

	if (args_count < 10)
	{
		cylinder->trans_x = 0.0;
		cylinder->trans_y = 0.0;
		cylinder->trans_z = 0.0;
		return ;
	}
	if (!ft_str_is_vector(args[9]))
	{
		cylinder->trans_x = 0.0;
		cylinder->trans_y = 0.0;
		cylinder->trans_z = 0.0;
		return ;
	}
	trans = create_vector(args[9]);
	cylinder->trans_x = trans.x;
	cylinder->trans_y = trans.y;
	cylinder->trans_z = trans.z;
}

void	parse_cylinder(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_cylinder	*cylinder;
	t_list		*node;
	int			args_count;

	args_count = ft_strlst_len(args);
	cylinder = create_cylinder(args);
	if (!cylinder)
		exit_error("Error parse_cylinder: ", scene);
	parse_cylinder_rotations(cylinder, args, args_count);
	parse_cylinder_translation(cylinder, args, args_count);
	if (has_texture)
		obj = create_object(CYLINDER, cylinder, scene->map->objects->size,
				(char *[2]){args[2], args[6]});
	else
		obj = create_object(CYLINDER, cylinder, scene->map->objects->size,
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
	ft_stack_add_back(scene->map->objects, node);
}

static void	parse_cone_rotations(t_cone *cone, char **args, int args_count)
{
	if (args_count < 7)
	{
		cone->rot_x = 0.0;
		cone->rot_y = 0.0;
		cone->rot_z = 0.0;
		return ;
	}
	if (!ft_strisdbl(args[6]))
	{
		cone->rot_x = 0.0;
		cone->rot_y = 0.0;
		cone->rot_z = 0.0;
		return ;
	}
	cone->rot_x = ft_atodbl(args[6]);
	if (args_count > 7 && ft_strisdbl(args[7]))
		cone->rot_y = ft_atodbl(args[7]);
	else
		cone->rot_y = 0.0;
	if (args_count > 8 && ft_strisdbl(args[8]))
		cone->rot_z = ft_atodbl(args[8]);
	else
		cone->rot_z = 0.0;
}

static void	parse_cone_translation(t_cone *cone, char **args, int args_count)
{
	t_vec	trans;

	if (args_count < 10)
	{
		cone->trans_x = 0.0;
		cone->trans_y = 0.0;
		cone->trans_z = 0.0;
		return ;
	}
	if (!ft_str_is_vector(args[9]))
	{
		cone->trans_x = 0.0;
		cone->trans_y = 0.0;
		cone->trans_z = 0.0;
		return ;
	}
	trans = create_vector(args[9]);
	cone->trans_x = trans.x;
	cone->trans_y = trans.y;
	cone->trans_z = trans.z;
}

void	parse_cone(char **args, t_scene *scene, int has_texture)
{
	t_object	*obj;
	t_cone		*cone;
	t_list		*node;
	int			args_count;

	args_count = ft_strlst_len(args);
	cone = create_cone(args);
	if (!cone)
		exit_error("Error parse_cone: ", scene);
	parse_cone_rotations(cone, args, args_count);
	parse_cone_translation(cone, args, args_count);
	if (has_texture)
		obj = create_object(CONE, cone, scene->map->objects->size,
				(char *[2]){args[2], args[6]});
	else
		obj = create_object(CONE, cone, scene->map->objects->size,
				(char *[2]){args[2], NULL});
	if (!obj)
		return (free_cone(cone),
			exit_error("Error parse_cone: ", scene));
	if (!create_color(args[5], &obj->color_range))
		exit_error("Error. Cone color_range: ", scene);
	node = ft_lstnew(obj);
	if (!node)
		return (free_object(obj),
			exit_error("Error. malloc\n", scene));
	ft_stack_add_back(scene->map->objects, node);
}


