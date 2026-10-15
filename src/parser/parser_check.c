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

static char	*color_err(char *s)
{
	t_color	tmp;

	if (ft_str_is_color(s) && create_color(s, &tmp))
		return (NULL);
	return ("colour (R,G,B 0-255)");
}

static int	ok_axis(char *s)
{
	t_vec	v;

	if (!ft_str_is_vector(s))
		return (0);
	v = create_vector(s);
	return (is_normalized_vec(v) && vector_dot_prod(v, v) > 1e-12);
}

/* Returns the name of the first invalid field, or NULL if the row is valid */
static char	*bad_field(char **a, int *idx)
{
	*idx = 1;
	if (!ft_str_is_vector(a[1]))
		return ("position (x,y,z)");
	*idx = 2;
	if (a[0][0] == 's')
	{
		if (!ft_strisdbl(a[2]) || ft_atodbl(a[2]) <= 0)
			return ("diameter (must be > 0)");
		return (*idx = 3, color_err(a[3]));
	}
	if (!ok_axis(a[2]))
		return ("orientation (each axis in [-1,1], not 0,0,0)");
	if (a[0][0] == 'p')
		return (*idx = 3, color_err(a[3]));
	*idx = 3;
	if (!ft_strisdbl(a[3]) || ft_atodbl(a[3]) <= 0)
		return ("diameter (must be > 0)");
	*idx = 4;
	if (!ft_strisdbl(a[4]) || ft_atodbl(a[4]) <= 0)
		return ("height (must be > 0)");
	return (*idx = 5, color_err(a[5]));
}

void	check_object_args(char **args, t_scene *scene)
{
	int		expected;
	int		idx;
	char	*field;
	char	msg[256];

	expected = expected_args(args[0]);
	if (!expected)
		return ;
	ft_strlcpy(msg, args[0], sizeof(msg));
	if ((int)ft_strlst_len(args) != expected && !(expected == 7
			&& ft_strlst_len(args) == 6))
		ft_strlcat(msg, ": wrong number of fields\n", sizeof(msg));
	else
	{
		field = bad_field(args, &idx);
		if (!field)
			return ;
		ft_strlcat(msg, ": invalid ", sizeof(msg));
		ft_strlcat(msg, field, sizeof(msg));
		ft_strlcat(msg, ": '", sizeof(msg));
		ft_strlcat(msg, args[idx], sizeof(msg));
		ft_strlcat(msg, "'\n", sizeof(msg));
	}
	exit_error(msg, scene);
}
