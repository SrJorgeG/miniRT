/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krusty <krusty@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:23:08 by krusty            #+#    #+#             */
/*   Updated: 2025/12/22 20:58:32 by krusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	parse_line_dispatcher(char **args, t_scene *scene)
{
	if (!ft_strcmp(*args, "A"))
		parse_ambient_light(args, scene);
	else if (!ft_strcmp(*args, "C"))
		parse_camera(args, scene);
	else if (!ft_strcmp(*args, "L"))
		parse_light(args, scene);
	else if (!ft_strcmp(*args, "sp"))
		parse_sphere(args, scene, 0);
	else if (!ft_strcmp(*args, "spt"))
		parse_sphere(args, scene, 1);
	else if (!ft_strcmp(*args, "pl"))
		parse_plane(args, scene, 0);
	else if (!ft_strcmp(*args, "plt"))
		parse_plane(args, scene, 1);
	else if (!ft_strcmp(*args, "cy"))
		parse_cylinder(args, scene, 0);
	else if (!ft_strcmp(*args, "cyt"))
		parse_cylinder(args, scene, 1);
	else
		exit_error("Error invalid map data, wrong identifier in row.\n", scene);
}

int	check_map(char *filename)
{
	int		fd;
	char	*cpy;

	cpy = filename;
	while (*cpy && *cpy != '.')
		cpy++;
	if (ft_strcmp(cpy, ".rt") != 0)
		exit_error("Error, invalid filename\n", NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("Error, invalid map file\n", NULL);
	return (fd);
}

void	parse_line(char *line, t_scene *scene)
{
	char	**args;
	char	delim[2];
	int		i;

	delim[0] = '\t';
	delim[1] = ' ';
	args = ft_split_2(line, delim);
	free(line);
	if (!args || !args[0])
	{
		ft_free_split(args);
		return ;
	}
	i = -1;
	while (args[++i])
		printf("%s\n", args[i]);
	parse_line_dispatcher(args, scene);
	ft_free_split(args);
}

void	trim_new_line(char *str)
{
	char	*cpy;

	cpy = str;
	while (*cpy)
	{
		if (*cpy == '\n')
			*cpy = '\0';
		cpy++;
	}
}

int	parser(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = check_map(filename);
	init_map(&scene->map);
	line = get_next_line(fd);
	while (line)
	{
		trim_new_line(line);
		if (line && ft_strlen(line) > 0)
			parse_line(line, scene);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
