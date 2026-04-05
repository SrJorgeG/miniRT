/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by krusty            #+#    #+#             */
/*   Updated: 2026/04/05 00:00:00 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse_ambient_light(char **args, t_scene *scene)
{
	if (scene->map->has_amb_light)
		exit_error("Error. Duplicated Ambient Light\n", scene);
	if (ft_strlst_len(args) != 3)
		exit_error("Error. Invalid map data, incompleted ambient_light row.\n",
			scene);
	if (!ft_strisdbl(args[1]) || !ft_str_is_color(args[2]))
		exit_error("Error invalid map data, wrong data in ambient_light row.\n",
			scene);
	scene->map->amb_ligt.amb_ratio = ft_atodbl(args[1]);
	if (!create_color(args[2], &scene->map->amb_ligt.amb_col))
		exit_error("Error. Ambient light color: ", scene);
	if (scene->map->amb_ligt.amb_ratio < 0.0
		|| scene->map->amb_ligt.amb_ratio > 1.0)
		exit_error("Error. Invalid range for ambient light ratio.", scene);
	scene->map->has_amb_light = 1;
}

static void	parse_camera_rotations(t_camera *camera, char **args,
		int args_count)
{
	if (args_count < 5)
	{
		camera->rot_x = 0.0;
		camera->rot_y = 0.0;
		camera->rot_z = 0.0;
		return ;
	}
	if (!ft_strisdbl(args[4]))
	{
		camera->rot_x = 0.0;
		camera->rot_y = 0.0;
		camera->rot_z = 0.0;
		return ;
	}
	camera->rot_x = ft_atodbl(args[4]);
	if (args_count > 5 && ft_strisdbl(args[5]))
		camera->rot_y = ft_atodbl(args[5]);
	else
		camera->rot_y = 0.0;
	if (args_count > 6 && ft_strisdbl(args[6]))
		camera->rot_z = ft_atodbl(args[6]);
	else
		camera->rot_z = 0.0;
}

void	parse_camera(char **args, t_scene *scene)
{
	int	args_count;

	if (scene->map->has_camera)
		exit_error("Error. Duplicated Camera\n", scene);
	args_count = ft_strlst_len(args);
	if (args_count < 4)
		exit_error("Error. Invalid map data, incompleted camera row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2])
		|| (!ft_strisnum(args[3]) || ft_strlen(args[3]) > 3))
		exit_error("Error invalid map data, wrong data in camera row.\n",
			scene);
	scene->map->camera.view_point = create_vector(args[1]);
	scene->map->camera.orientation_nor = create_vector(args[2]);
	scene->map->camera.fov = ft_atoi(args[3]);
	if (!is_normalized_vec(scene->map->camera.orientation_nor))
		exit_error("Error. Invalid range for camera orientation.", scene);
	if (scene->map->camera.fov < 0 || scene->map->camera.fov > 180)
		exit_error("Error. Invalid range for camera FOV.", scene);
	parse_camera_rotations(&scene->map->camera, args, args_count);
	scene->map->has_camera = 1;
}

static void	parse_light_translation(t_light *light, char **args,
		int args_count)
{
	t_vec	trans;

	if (args_count < 5)
	{
		light->trans_x = 0.0;
		light->trans_y = 0.0;
		light->trans_z = 0.0;
		return ;
	}
	if (!ft_str_is_vector(args[4]))
	{
		light->trans_x = 0.0;
		light->trans_y = 0.0;
		light->trans_z = 0.0;
		return ;
	}
	trans = create_vector(args[4]);
	light->trans_x = trans.x;
	light->trans_y = trans.y;
	light->trans_z = trans.z;
}

void	parse_light(char **args, t_scene *scene)
{
	t_light	*light;
	t_list	*node;
	int		args_count;

	if (scene->map->has_lights)
		exit_error("Error. Duplicated Light\n", scene);
	light = malloc(sizeof(t_light));
	if (!light)
		exit_error("Error. t_light malloc\n", scene);
	args_count = ft_strlst_len(args);
	if (args_count < 4)
		exit_error("Error. Invalid map data, incompleted light row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_strisdbl(args[2])
		|| !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in light row.\n", scene);
	light->light_point = create_vector(args[1]);
	light->brightness = ft_atodbl(args[2]);
	if (!create_color(args[3], &light->color_range))
		exit_error("Error. Light color range: ", scene);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		exit_error("Error. Invalid range for light FOV.", scene);
	parse_light_translation(light, args, args_count);
	node = ft_lstnew(light);
	if (!node)
		return (free(light),
			exit_error("Error.parse_light: ft_lstnew: malloc\n", scene));
	ft_stack_add_back(scene->map->lights, node);
	scene->map->has_lights = 1;
}

