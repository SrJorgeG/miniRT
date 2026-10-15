/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:10:05 by dcid-san          #+#    #+#             */
/*   Updated: 2026/03/29 22:49:26 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	exit_error(char *err_msg, t_scene *scene)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (!ft_strncmp(err_msg, "Error", 5))
		err_msg += 5;
	while (*err_msg == '.' || *err_msg == ',' || *err_msg == ' ')
		err_msg++;
	ft_putstr_fd(err_msg, STDERR_FILENO);
	if (*err_msg && err_msg[ft_strlen(err_msg) - 1] != '\n')
		ft_putstr_fd("\n", STDERR_FILENO);
	free_scene(scene);
	exit(1);
}
