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
		exit_error("Error. Invalid map data, incompleted row.\n", map);
	if(!ft_strisdbl(args[1]) || !ft_str_is_vector(args[2]) )
		exit_error("Error invalid map data, wrong data in row.\n", map);
	amb_light->amb_col = create_vector(args[2]);
	amb_light->amb_ratio = ft_atodbl(args[1]);
	if (amb_light->amb_ratio < 0.0 || amb_light->amb_ratio > 1.0)
		exit_error("Error. Invalid range for ambient light ratio.", map);
	map->amb_ligt = amb_light;
}

void	parse_line(char *line, t_map *map)
{
	char	**args;

	args = ft_split(line, '\t');
	if (ft_strcmp(*args, "A"))
		parse_ambient_light(args, map);
	else if (ft_strcmp(*args, "C"))
	{
		/* code */
	}
	else if (ft_strcmp(*args, "C"))
	{
		/* code */
	}
	else if (ft_strcmp(*args, "C"))
	{
		/* code */
	}
	else if (ft_strcmp(*args, "C"))
	{
		/* code */
	}
	
	

}

t_map	*parser(char *filename)
{
	int fd;
	char *line;
	t_map *map;

	fd = check_map(filename);
	map = ft_calloc(sizeof(t_map), 1);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, map);
		free(line);
		line = get_next_line(fd);
	}
	

}