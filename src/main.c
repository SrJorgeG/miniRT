/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:39:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/12/22 20:05:27 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	main(int ac, char *av[])
{
	t_scene		*scene;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (ac != 2)
		exit_error("Error, invalid number of arguments\n", NULL);
	scene = malloc(sizeof(t_scene));
	parser(av[1], scene);
	setup_camera(&scene->map.camera);
	setup_scene(scene, &scene->map.camera);
	init_cache(scene);
	debug_scene(scene);
	mlx = mlx_init(WIDTH, HEIGHT, TITLE, 0);
	if (!mlx)
		exit_error("Error. mlx_init\n", NULL);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	
	if (!img)
		exit_error("Error. mlx_new_image\n", NULL);
	render(scene, mlx, img);
	//mlx_key_hook(mlx, custom_key_hook, &(t_hook_data){scene, mlx, img});
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	//mlx_put_string();
	mlx_terminate(mlx);
	free_scene(scene);
}
