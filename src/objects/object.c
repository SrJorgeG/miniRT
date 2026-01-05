#include "../../include/minirt.h"


/* CHECKEAR SI UNA TEXTURA NO VALIDA NO CREA LEAKS ASI, 
SINO LLAMAR A FREE_OBJECT Y MODIFICAR FREE_OBJECT PARA QUE CHECKEE NULL 
ANTES DE FREE OBJECT->OBJECT */
t_object	*create_object(int obj_type, void *object, size_t id, char *texture_path)
{
	t_object	*obj;
	int			texture_fd;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	obj->texture_path = NULL;
	obj->texture = NULL;
	if (texture_path)
	{
		texture_fd = open(texture_path, O_RDONLY);
    	if (texture_fd < 0)
			return (free(obj), NULL);
		close(texture_fd);
		obj->texture_path = ft_strdup(texture_path);
	}
	if (!load_texture(obj))
		return (free(obj), NULL);	
	obj->object = object;
	obj->type = obj_type;
	obj->id = id;
	return (obj);
}

void	free_object(void *object)
{
	t_object *obj;
	
	obj = (t_object *)object;
	if (obj->texture)
		mlx_delete_texture(obj->texture);
	if (obj->texture_path)
		free(obj->texture_path);
	if (obj->type == SPHERE)
		free_sphere(obj->object);
	if (obj->type == CYLINDER)
		free_cylinder(obj->object);
	if (obj->type == PLANE)
		free_plane(obj->object);
	free(obj);
}
