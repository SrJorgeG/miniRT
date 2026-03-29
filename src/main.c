/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:39:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/03/29 22:49:15 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	init_mlx_and_render(t_scene *scene, char *title)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, title, 0);
	if (!scene->mlx)
		exit_error("Error. mlx_init\n", scene);
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->img)
		exit_error("Error. mlx_new_image\n", scene);
	render(scene, scene->mlx, scene->img);
	mlx_key_hook(scene->mlx, custom_key_hook,
		&(t_hook_data){scene, scene->mlx, scene->img});
	mlx_mouse_hook(scene->mlx, custom_mouse_hook,
		&(t_hook_data){scene, scene->mlx, scene->img});
	mlx_loop(scene->mlx);
	mlx_delete_image(scene->mlx, scene->img);
	mlx_terminate(scene->mlx);
	scene->mlx = NULL;
	scene->img = NULL;
}

static void	init_scene_and_camera(t_scene *scene, char *filename)
{
	scene->map = NULL;
	scene->mlx = NULL;
	scene->img = NULL;
	scene->pixel_cache = NULL;
	scene->args = NULL;
	parser(filename, scene);
	setup_camera(&scene->map->camera);
	setup_scene(scene, &scene->map->camera);
	init_cache(scene);
}

int	main(int ac, char *av[])
{
	t_scene	*scene;

	scene = NULL;
	if (ac != 2)
		exit_error("Error, invalid number of arguments\n", NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit_error("Error, malloc of t_scene\n", NULL);
	init_scene_and_camera(scene, av[1]);
	init_mlx_and_render(scene, TITLE);
	free_scene(scene);
	return (0);
}
