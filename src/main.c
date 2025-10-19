/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:39:54 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/19 17:22:11 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	main(int ac, char *av[])
{
	t_map *map;
	mlx_t	*mlx;
	mlx_image_t* img;
	int32_t		heigth = 0;
	int32_t		width = 0;
	
	if(ac != 2)
		exit_error("Error, invalid number of arguments\n", NULL);
	
	map = parser(av[1]);
	debug_map(map);

	mlx = mlx_init(WIDTH, HEIGHT, TITLE, 0);
	if (!mlx)
		exit_error("Error. mlx_init\n", NULL);

	
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		exit_error("Error. mlx_new_image\n", NULL);

	
	while (heigth < HEIGHT)
	{
		width = 0;
		while (width < WIDTH)
		{
			mlx_put_pixel(img, width, heigth, get_rgba(255,73,39, 255));
			width++;
		}
		heigth++;
	}
	
	



	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
    	exit_error("Error. mlx_image_to_window\n", NULL);

	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	free_map(map);
}
