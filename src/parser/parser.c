#include "../../include/minirt.h"

int	check_map(char *filename)
{
	int	fd;
	char *cpy;

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

void	parse_ambient_light(char **args, t_map *map)
{
	t_amb_light *amb_light;

	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		exit_error("Error. malloc\n", map);
	if (ft_strlst_len(args) != 3)
		exit_error("Error. Invalid map data, incompleted ambient_light row.\n", map);
	if(!ft_strisdbl(args[1]) || !ft_str_is_color(args[2]) )
		exit_error("Error invalid map data, wrong data in ambient_light row.\n", map);
	amb_light->amb_col = create_color(args[2]);
	amb_light->amb_ratio = ft_atodbl(args[1]);
	if (!amb_light->amb_col)
		exit_error("Error. Ambient light color: ", map);
	if (amb_light->amb_ratio < 0.0 || amb_light->amb_ratio > 1.0)
		exit_error("Error. Invalid range for ambient light ratio.", map);
	map->amb_ligt = amb_light;
}

void	parse_camera(char **args, t_map *map)
{
	t_camera *camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		exit_error("Error. malloc\n", map);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted camera row.\n", map);
	if(!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2]) || (!ft_strisnum(args[3]) || ft_strlen(args[3]) > 3))
		exit_error("Error invalid map data, wrong data in camera row.\n", map);
	camera->view_point = create_vector(args[1]);
	camera->vector = create_vector(args[2]);
	camera->fov = ft_atoi(args[3]);
	if (!is_normalized_vec(camera->vector))
		exit_error("Error. Invalid range for camera orientation.", map);
	if( camera->fov < 0 || camera->fov > 180)
		exit_error("Error. Invalid range for camera FOV.", map);
	map->camera = camera;
}

void	parse_light(char **args, t_map *map)
{
	t_light *light;

	light = malloc(sizeof(t_light));
	if (!light)
		exit_error("Error. malloc\n", map);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted light row.\n", map);
	if(!ft_str_is_vector(args[1]) || !ft_strisdbl(args[2]) || !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in light row.\n", map);
	light->light_point = create_vector(args[1]);
	light->brightness = ft_atodbl(args[2]);
	light->color_range = create_color(args[3]);
	if (!light->color_range)
		exit_error("Error. Light color range: ", map);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		exit_error("Error. Invalid range for light FOV.", map);
	map->light = light;
}

void parse_sphere(char **args, t_map *map)
{
	t_sphere *sphere;
	t_list	*node;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit_error("Error. malloc\n", map);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted sphere row.\n", map);
	if(!ft_str_is_vector(args[1]) || !ft_strisdbl(args[2]) || !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in sphere row.\n", map);
	sphere->center = create_vector(args[1]);
	sphere->diameter = ft_atodbl(args[2]);
	sphere->color_range = create_color(args[3]);
	if (!sphere->color_range)
		exit_error("Error. Sphere color_range: ", map);
	if (sphere->diameter <= 0.0)
		exit_error("Error. Invalid range for sphere diameter.", map);
	node = ft_lstnew(sphere);
	if (!node)
		exit_error("Error. malloc\n", map);
	ft_stack_add_back(map->spheres, node);
}

void parse_plane(char **args, t_map *map)
{
	t_plane *plane;
	t_list	*node;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit_error("Error. malloc\n", map);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted plane row.\n", map);
	if(!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2]) || !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in plane row.\n", map);
	plane->point = create_vector(args[1]);
	plane->vector = create_vector(args[2]);
	plane->color_range = create_color(args[3]);
	if (!plane->color_range)
		exit_error("Error. Plane color_range: ", map);
	if (!is_normalized_vec(plane->vector))
		exit_error("Error. Invalid range for plane orientation.", map);
	node = ft_lstnew(plane);
	if (!node)
		exit_error("Error. malloc\n", map);
	ft_stack_add_back(map->planes, node);
}

void	parse_cylinder(char **args, t_map *map)
{
	t_cylinder *cylinder;
	t_list	*node;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		exit_error("Error. malloc\n", map);
	if (ft_strlst_len(args) != 6)
		exit_error("Error. Invalid map data, incompleted cylinder row.\n", map);
	if(!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2]) 
		|| (!ft_strisdbl(args[3])) || (!ft_strisdbl(args[4])) 
		|| (!ft_str_is_color(args[5])))
		exit_error("Error invalid map data, wrong data in cylinder row.\n", map);
	cylinder->center = create_vector(args[1]);
	cylinder->axys = create_vector(args[2]);
	cylinder->diameter = ft_atodbl(args[3]);
	cylinder->height = ft_atodbl(args[4]);
	cylinder->color_range = create_color(args[5]);
	if (!cylinder->color_range)
		exit_error("Error. Cylinder color_range: ", map);
	if (!is_normalized_vec(cylinder->axys))
		exit_error("Error. Invalid range for cylinder orientation.", map);
	if (cylinder->diameter <= 0.0)
		exit_error("Error. Invalid range for cylinder diameter.", map);
	if (cylinder->height <= 0.0)
		exit_error("Error. Invalid range for cylinder height.", map);
	node = ft_lstnew(cylinder);
	if (!node)
		exit_error("Error. malloc\n", map);
	ft_stack_add_back(map->cylinders, node);
}

void	parse_line(char *line, t_map *map)
{
	char	**args;

	args = ft_split(line, '\t');
	free(line);
	if (!ft_strcmp(*args, "A"))
		parse_ambient_light(args, map);
	else if (!ft_strcmp(*args, "C"))
		parse_camera(args, map);
	else if (!ft_strcmp(*args, "L"))
		parse_light(args, map);
	else if (!ft_strcmp(*args, "sp"))
		parse_sphere(args, map);
	else if (!ft_strcmp(*args, "pl"))
		parse_plane(args, map);
	else if (!ft_strcmp(*args, "cy"))
		parse_cylinder(args, map);
	else
		exit_error("Error invalid map data, wrong identifier in row.\n", map);
	ft_free_split(args);
}

void	trim_new_line(char *str)
{
	char *cpy;

	cpy = str;
	while (*cpy)
	{
		if (*cpy == '\n')
			*cpy = '\0';
		cpy++;
	}
}

t_map	*parser(char *filename)
{
	int fd;
	char *line;
	t_map *map;

	fd = check_map(filename);
	map = init_map();
	line = get_next_line(fd);
	while (line)
	{
		trim_new_line(line);
		parse_line(line, map);
		line = get_next_line(fd);
	}
	close(fd);
	return(map);
	
}