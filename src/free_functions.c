/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:39:18 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 21:07:23 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	free_cache(t_scene *scene)
{
	int	i;

	if (!scene || !scene->pixel_cache)
		return ;
	i = 0;
	while (i < scene->cache_count)
	{
		free(scene->pixel_cache[i].pixels);
		scene->pixel_cache[i].pixels = NULL;
		i++;
	}
	free(scene->pixel_cache);
	scene->pixel_cache = NULL;
	scene->cache_count = 0;
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_cache(scene);
	if (scene->map)
		free_map(scene->map);
	if (scene->img)
		mlx_delete_image(scene->mlx, scene->img);
	if (scene->mlx)
		mlx_terminate(scene->mlx);
	free(scene);
}