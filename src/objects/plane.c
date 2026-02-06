#include "../../include/minirt.h"

t_plane *create_plane(char **args)
{
	t_plane *plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = create_vector(args[1]);
	plane->vector = create_vector(args[2]);
	return (plane);
}