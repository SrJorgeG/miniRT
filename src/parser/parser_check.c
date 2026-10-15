/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:30:00 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/10/15 12:30:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	expected_args(char *id)
{
	if (!ft_strcmp(id, "sp") || !ft_strcmp(id, "pl"))
		return (4);
	if (!ft_strcmp(id, "plt"))
		return (5);
	if (!ft_strcmp(id, "spt") || !ft_strcmp(id, "cy") || !ft_strcmp(id, "co"))
		return (6);
	if (!ft_strcmp(id, "cyt") || !ft_strcmp(id, "cot"))
		return (7);
	return (0);
}

static int	valid_values(char **args)
{
	if (!ft_str_is_vector(args[1]))
		return (0);
	if (args[0][0] == 's')
		return (ft_strisdbl(args[2]) && ft_str_is_color(args[3]));
	if (!ft_str_is_vector(args[2]))
		return (0);
	if (args[0][0] == 'p')
		return (ft_str_is_color(args[3]));
	return (ft_strisdbl(args[3]) && ft_strisdbl(args[4])
		&& ft_str_is_color(args[5]));
}

void	check_object_args(char **args, t_scene *scene)
{
	int	expected;

	expected = expected_args(args[0]);
	if (!expected)
		return ;
	if ((int)ft_strlst_len(args) != expected && !(expected == 7
			&& ft_strlst_len(args) == 6))
	{
		ft_free_split(args);
		exit_error("Error. Wrong number of fields in object row.\n", scene);
	}
	if (!valid_values(args))
	{
		ft_free_split(args);
		exit_error("Error. Invalid value in object row.\n", scene);
	}
}
