#include "../../include/minirt.h"
#include "../../include/geo_trans.h"

int check_map(char *filename)
{
	int fd;
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

void parse_ambient_light(char **args, t_scene *scene)
{
	t_amb_light *amb_light;

	if (scene->map.has_amb_ligt)
		exit_error("Error. Duplicated Ambient Light\n", scene);

	amb_light = malloc(sizeof(t_amb_light));
	if (!amb_light)
		exit_error("Error. malloc\n", scene);
	if (ft_strlst_len(args) != 3)
		exit_error("Error. Invalid map data, incompleted ambient_light row.\n", scene);
	if (!ft_strisdbl(args[1]) || !ft_str_is_color(args[2]))
		exit_error("Error invalid map data, wrong data in ambient_light row.\n", scene);
	scene->map.amb_ligt.amb_ratio = ft_atodbl(args[1]);
	if (!create_color(args[2], &scene->map.amb_ligt.amb_col))
		exit_error("Error. Ambient light color: ", scene);
	if (scene->map.amb_ligt.amb_ratio < 0.0 || scene->map.amb_ligt.amb_ratio > 1.0)
		exit_error("Error. Invalid range for ambient light ratio.", scene);
	scene->map.has_amb_ligt = 1;
}

void parse_camera(char **args, t_scene *scene)
{

	if (scene->map.has_camera)
		exit_error("Error. Duplicated Camera\n", scene);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted camera row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2]) || (!ft_strisnum(args[3]) || ft_strlen(args[3]) > 3))
		exit_error("Error invalid map data, wrong data in camera row.\n", scene);
	scene->map.camera.view_point = create_vector(args[1]);
	scene->map.camera.orientation_nor = create_vector(args[2]);
	scene->map.camera.fov = ft_atoi(args[3]);
	if (!is_normalized_vec(scene->map.camera.orientation_nor))
		exit_error("Error. Invalid range for camera orientation.", scene);
	if (scene->map.camera.fov < 0 || scene->map.camera.fov > 180)
		exit_error("Error. Invalid range for camera FOV.", scene);
	scene->map.has_camera = 1;
}

void parse_light(char **args, t_scene *scene)
{
	t_light *light;
	t_list *node;

	if (scene->map.has_lights)
		exit_error("Error. Duplicated Light\n", scene);
	light = malloc(sizeof(t_light));
	if (!light)
		exit_error("Error. malloc\n", scene);
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted light row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_strisdbl(args[2]) || !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in light row.\n", scene);
	light->light_point = create_vector(args[1]);
	light->brightness = ft_atodbl(args[2]);
	if (!create_color(args[3], &light->color_range))
		exit_error("Error. Light color range: ", scene);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		exit_error("Error. Invalid range for light FOV.", scene);
	node = ft_lstnew(light);
	if (!node)
		exit_error("Error. malloc\n", scene);
	ft_stack_add_back(scene->map.lights, node);
}

void parse_sphere(char **args, t_scene *scene)
{
	t_object *obj;
	t_sphere *sphere;
	t_list *node;

	obj = malloc(sizeof(t_object));
	sphere = malloc(sizeof(t_sphere));
	if (!sphere || !obj)
		exit_error("Error. malloc\n", scene);
	obj->object = sphere;
	obj->type = SPHERE;
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted sphere row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_strisdbl(args[2]) || !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in sphere row.\n", scene);
	sphere->center = create_vector(args[1]);
	sphere->diameter = ft_atodbl(args[2]);
	sphere->radius = sphere->diameter / 2;
	if (!create_color(args[3], &obj->color_range))
		exit_error("Error. Sphere color_range: ", scene);
	if (sphere->diameter <= 0.0)
		exit_error("Error. Invalid range for sphere diameter.", scene);
	node = ft_lstnew(obj);
	if (!node)
		exit_error("Error. malloc\n", scene);
	ft_stack_add_back(scene->map.objects, node);
}

void parse_plane(char **args, t_scene *scene)
{
	t_object *obj;
	t_plane *plane;
	t_list *node;

	obj = malloc(sizeof(t_object));
	plane = malloc(sizeof(t_plane));
	if (!plane || !obj)
		exit_error("Error. malloc\n", scene);
	obj->object = plane;
	obj->type = PLANE;
	if (ft_strlst_len(args) != 4)
		exit_error("Error. Invalid map data, incompleted plane row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2]) || !ft_str_is_color(args[3]))
		exit_error("Error invalid map data, wrong data in plane row.\n", scene);
	plane->point = create_vector(args[1]);
	plane->vector = create_vector(args[2]);
	if (!create_color(args[3], &obj->color_range))
		exit_error("Error. Plane color_range: ", scene);
	if (!is_normalized_vec(plane->vector))
		exit_error("Error. Invalid range for plane orientation.", scene);
	node = ft_lstnew(obj);
	if (!node)
		exit_error("Error. malloc\n", scene);
	ft_stack_add_back(scene->map.objects, node);
}

void parse_cylinder(char **args, t_scene *scene)
{
	t_object *obj;
	t_cylinder *cylinder;
	t_list *node;

	obj = malloc(sizeof(t_object));
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder || !obj)
		exit_error("Error. malloc\n", scene);
	obj->object = cylinder;
	obj->type = CYLINDER;
	if (ft_strlst_len(args) != 6)
		exit_error("Error. Invalid map data, incompleted cylinder row.\n", scene);
	if (!ft_str_is_vector(args[1]) || !ft_str_is_vector(args[2]) || (!ft_strisdbl(args[3])) || (!ft_strisdbl(args[4])) || (!ft_str_is_color(args[5])))
		exit_error("Error invalid map data, wrong data in cylinder row.\n", scene);
	cylinder->center = create_vector(args[1]);
	cylinder->axys = create_vector(args[2]);
	cylinder->diameter = ft_atodbl(args[3]);
	cylinder->height = ft_atodbl(args[4]);
	// 1. FORWARD transform: espacio canónico → mundo
	cylinder->transform = cylinder_build_transform(cylinder->center, cylinder->axys, cylinder->height);

	// 2. BACKWARD transform: mundo → espacio canónico
	cylinder->inverse_transform = mat4_inverse(cylinder->transform);

	if (!create_color(args[5], &obj->color_range))
		exit_error("Error. Cylinder color_range: ", scene);
	if (!is_normalized_vec(cylinder->axys))
		exit_error("Error. Invalid range for cylinder orientation.", scene);
	if (cylinder->diameter <= 0.0)
		exit_error("Error. Invalid range for cylinder diameter.", scene);
	if (cylinder->height <= 0.0)
		exit_error("Error. Invalid range for cylinder height.", scene);
	node = ft_lstnew(obj);
	if (!node)
		exit_error("Error. malloc\n", scene);
	ft_stack_add_back(scene->map.objects, node);
}

void parse_line(char *line, t_scene *scene)
{
	char **args;

	args = ft_split(line, '\t');
	free(line);
	if (!args || !args[0])
	{
		ft_free_split(args);
		return;
	}
	if (!ft_strcmp(*args, "A"))
		parse_ambient_light(args, scene);
	else if (!ft_strcmp(*args, "C"))
		parse_camera(args, scene);
	else if (!ft_strcmp(*args, "L"))
		parse_light(args, scene);
	else if (!ft_strcmp(*args, "sp"))
		parse_sphere(args, scene);
	else if (!ft_strcmp(*args, "pl"))
		parse_plane(args, scene);
	else if (!ft_strcmp(*args, "cy"))
		parse_cylinder(args, scene);
	else
		exit_error("Error invalid map data, wrong identifier in row.\n", scene);
	ft_free_split(args);
}

void trim_new_line(char *str)
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

/* ◦ Elements defined by a capital letter can only be declared once in the scene. */
int parser(char *filename, t_scene *scene)
{
	int fd;
	char *line;

	fd = check_map(filename);
	init_map(&scene->map);
	line = get_next_line(fd);
	while (line)
	{
		trim_new_line(line);
		if (line)
		{
			parse_line(line, scene);
		}
		line = get_next_line(fd);
	}

	close(fd);
	return (1);
}
