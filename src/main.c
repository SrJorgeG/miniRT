/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:39:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/12/22 20:13:40 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	init_mlx_and_render(t_scene *scene, char *title)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, title, 0);
	if (!mlx)
		exit_error("Error. mlx_init\n", NULL);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		exit_error("Error. mlx_new_image\n", NULL);
	render(scene, mlx, img);
	mlx_key_hook(mlx, custom_key_hook, &(t_hook_data){scene, mlx, img});
	mlx_mouse_hook(mlx, custom_mouse_hook, &(t_hook_data){scene, mlx, img});
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
}

static void	init_scene_and_camera(t_scene *scene, char *filename)
{
	parser(filename, scene);
	setup_camera(&scene->map.camera);
	setup_scene(scene, &scene->map.camera);
	init_cache(scene);
	debug_scene(scene);
}

int	main(int ac, char *av[])
{
	t_scene	*scene;

	if (ac != 2)
		exit_error("Error, invalid number of arguments\n", NULL);
	scene = malloc(sizeof(t_scene));
	init_scene_and_camera(scene, av[1]);
	init_mlx_and_render(scene, TITLE);
	free_scene(scene);
	return (0);
}
