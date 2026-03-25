/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by krusty            #+#    #+#             */
/*   Updated: 2025/12/22 20:58:32 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	parse_ambient_light(char **args, t_scene *scene)
{
	t_amb_light	*amb_light;

	if (scene->map.has_amb_ligt)
		exit_error("Error. Duplicated Ambient Light\n", scene);
	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		exit_error("Error. amb_light malloc\n", scene);
	if (ft_strlst_len(args) != 3)
		exit_error("Error. Invalid map data, incompleted ambient_light row.\n",
			scene);
	if (!ft_strisdbl(args[1]) || !ft_str_is_color(args[2]))
		exit_error("Error invalid map data, wrong data in ambient_light row.\n",
			scene);
	scene->map.amb_ligt.amb_ratio = ft_atodbl(args[1]);
	if (!create_color(args[2], &scene->map.amb_ligt.amb_col))
		exit_error("Error. Ambient light color: ", scene);
	if (scene->map.amb_ligt.amb_ratio < 0.0
		|| scene->map.amb_ligt.amb_ratio > 1.0)
		exit_error("Error. Invalid range for ambient light ratio.", scene);
	scene->map.has_amb_ligt = 1;
}

void	parse_camera(char **args, t_scene *scene)
{
	if (scene->map.has_camera)
		exit_error("Error. Duplicated Camera\n", scene);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted camera row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2])
		|| (!ft_strisnum(args[3]) || ft_strlen(args[3]) > 3))
		exit_error("Error invalid map data, wrong data in camera row.\n",
			scene);
	scene->map.camera.view_point = create_vector(args[1]);
	scene->map.camera.orientation_nor = create_vector(args[2]);
	scene->map.camera.fov = ft_atoi(args[3]);
	if (!is_normalized_vec(scene->map.camera.orientation_nor))
		exit_error("Error. Invalid range for camera orientation.", scene);
	if (scene->map.camera.fov < 0 || scene->map.camera.fov > 180)
		exit_error("Error. Invalid range for camera FOV.", scene);
	scene->map.has_camera = 1;
}

void	parse_light(char **args, t_scene *scene)
{
	t_light	*light;
	t_list	*node;

	if (scene->map.has_lights)
		exit_error("Error. Duplicated Light\n", scene);
	light = malloc(sizeof(t_light));
	if (!light)
		exit_error("Error. t_light malloc\n", scene);
	if (ft_strlst_len(args) != 4)
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
	node = ft_lstnew(light);
	if (!node)
		exit_error("Error.parse_light: ft_lstnew: malloc\n", scene);
	ft_stack_add_back(scene->map.lights, node);
}
