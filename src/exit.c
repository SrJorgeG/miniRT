/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:10:05 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/27 20:57:34 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	exit_error(char *err_msg, t_scene *scene)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
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
	exit(1);
}