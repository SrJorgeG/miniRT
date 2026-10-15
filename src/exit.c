/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 19:10:05 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/13 15:40:33 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	exit_error(char *err_msg, void *free_data)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (!ft_strncmp(err_msg, "Error", 5))
		err_msg += 5;
	while (*err_msg == '.' || *err_msg == ',' || *err_msg == ' ')
		err_msg++;
	ft_putstr_fd(err_msg, STDERR_FILENO);
	if (*err_msg && err_msg[ft_strlen(err_msg) - 1] != '\n')
		ft_putstr_fd("\n", STDERR_FILENO);
	if (free_data)
		free_scene(free_data);
	exit(1);
}
