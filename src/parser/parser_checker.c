/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:30:00 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:30:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	apply_checker(char **args, t_scene *scene)
{
	t_object	*obj;

	if (ft_strcmp(args[0], "sp") && ft_strcmp(args[0], "pl")
		&& ft_strcmp(args[0], "cy") && ft_strcmp(args[0], "co"))
	{
			exit_error("Error. 'checker' is only valid on sp, pl, cy, co rows\n",
			scene);
	}
	obj = scene->map->objects->last->content;
	obj->checker = 1;
}

int	strip_checker(char **args)
{
	int	n;

	n = ft_strlst_len(args);
	if (n < 2 || ft_strcmp(args[n - 1], "checker"))
		return (0);
	free(args[n - 1]);
	args[n - 1] = NULL;
	return (1);
}
