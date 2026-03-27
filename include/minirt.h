/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:37 by jgomez-d          #+#    #+#             */
/*   Updated: 2026/03/27 20:58:19 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#if !defined(MINIRT_H)
# define MINIRT_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <memory.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
/* 				MLX DEFINES				*/
# define WIDTH 600
# define HEIGHT 600
# define TITLE "MiniRT - De tu padre"

# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f
# define FOCAL 1
typedef double			t_real;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}						t_object_type;

typedef struct s_vector_2d
{
	double				x;
	double				y;
}						t_vec2;

typedef struct s_vector
{
	double				x;
	double				y;
	double				z;

}						t_vec;

typedef struct s_vector	t_point;
typedef struct s_color
{
	uint8_t					r;
	uint8_t					g;
	uint8_t					b;

} t_color; // [0-255]

typedef struct s_ray
{
	t_vec				origin;
	t_vec				direction;

}						t_ray;

typedef struct s_amb_light
{
	t_color				amb_col;
	float amb_ratio; // [0.0,1.0]

}						t_amb_light;

typedef struct s_camera
{
	t_vec				view_point;
	t_vec				orientation_nor;
	t_vec				right;
	t_vec				up;
	int					fov;
	unsigned int		focal;
	double				radial_fov;

}						t_camera;

typedef struct s_light
{
	t_vec				light_point;
	float brightness;    // [0.0,1.0]
	t_color color_range; // BONUS

}						t_light;

typedef struct s_sphere
{
	t_vec				center;
	double				diameter;
	double				radius;
}						t_sphere;

typedef struct s_plane
{
	t_vec				point;
	t_vec vector; // [-1,1]
}						t_plane;

typedef struct s_cylinder
{
	t_vec				center;
	t_vec axis; // [-1,1]
	double				diameter;
	double				height;

}						t_cylinder;

typedef struct s_cone
{
	t_vec				top;
	t_vec				axis;
	double				diameter;
	double				height;
}						t_cone;

typedef struct s_object
{
	t_object_type		type;
	void				*object;
	t_vec				center;
	t_vec				orientation;
	char				*texture_path;
	mlx_texture_t		*texture;
	t_color				color_range;
	size_t				id;
}						t_object;

typedef struct s_obj_cache
{
	int					obj_id;
	uint32_t			*pixels;
	uint32_t			pixel_count;
	uint32_t			capacity;
}						t_obj_cache;

typedef struct s_map
{
	t_camera			camera;
	t_stack				*objects;
	t_object			*last_hit;
	t_stack				*lights;
	t_amb_light			amb_ligt;
	uint8_t				has_camera;
	uint8_t				has_amb_ligt;
	uint8_t				has_lights;
}						t_map;

typedef struct s_scene
{
	t_real				aspect;
	t_real				viewport;
	t_map				*map;
	bool				is_rendered;
	bool				is_obj_picked;
	t_object			*picked_obj;
	int					screen_w;
	int					screen_h;
	int					cache_count;
	t_obj_cache			*pixel_cache;
	t_real				viewport_w;
	t_real				viewport_h;
	t_vec				image_center;
	mlx_t				*mlx;
	mlx_image_t			*img;
}						t_scene;

typedef struct s_hook_data
{
	t_scene				*scene;
	mlx_t				*mlx;
	mlx_image_t			*image;
}						t_hook_data;

/* Struct usado para guardar informacion del choque de un t_ray */
typedef struct s_hit
{
	int					hit;
	double				t;
	t_vec				p;
	t_vec				normal;
	t_color				color;
	t_object			*object;
}						t_hit;


void					exit_error(char *err_msg, t_scene *free_data);

/* STRING UTILLS */
char					**ft_split_2(char const *s, char c[2]);

/* VECTOR UTILS - src/utils/vector.c */
int						ft_str_is_vector(char *str);
t_vec					create_vector(char *vector_str);
int						is_normalized_vec(t_vec vector);
t_vec					*vector_constructor(double x, double y, double z);
void					vector_destructor(t_vec *vector);

/* VECTOR_BASIC - src/utils/vector_basic.c */
t_vec					vector_sum(t_vec v1, t_vec v2);
t_vec					vector_rest(t_vec v1, t_vec v2);
t_vec					vector_multiplication(t_vec v1, double num);
t_vec					vector_division(t_vec v1, double num);
t_vec					*vector_dup(t_vec vec);
t_vec					vector_scale(t_vec vec, double scalar);


/* VECTOR_AUX - src/utils/vector_aux.c */
double					vector_lenght_square(t_vec *vec);
double					vector_lenght(t_vec vec);
t_vec					vector_normalize(t_vec vec);
double					vector_dot_prod(t_vec v1, t_vec v2);
t_vec					vector_cross_prod(t_vec v1, t_vec v2);

/*		Hit functionss 	*/
int						hit_sphere(t_ray ray, t_sphere *sphere,
						double *obj_distance);
int						hit_plane(t_ray ray, t_plane *plane,
						double *obj_distance);
int						hit_cone(t_ray ray, t_object *obj,
						t_cone *cone, double *obj_distance);
void					get_cone_normal(t_hit *hit, t_object *obj,
						t_cone *cone, t_ray ray);
t_hit	get_hits(t_scene *scene, t_ray ray);
t_ray	get_ray_from_pixel(t_scene *scene, t_vec image_center,
		t_vec pixel_center);
t_vec	find_pixel_on_viewport(int x, int y, t_scene *scene);
/* COLOR UTILS - src/utils/color.c */
int						ft_str_is_color(char *str);

u_int8_t				create_color(char *color_str, t_color *color);

t_color					color_multiply(t_color c1, t_color c2);
t_color					color_scale(t_color c, double factor);
t_color					color_add(t_color c1, t_color c2);
void 					color_clamp(int c[3]);
int						color_to_int_no_alpha(t_color color);
int color_to_int_alpha(t_color color, uint8_t opacity);

t_color	calculate_lighting(t_hit *hit, t_scene *scene);

void					init_map(t_scene *scene);
void					render(t_scene *scene, mlx_t *mlx, mlx_image_t *img);
void					setup_camera(t_camera *camera);
void					setup_scene(t_scene *scene, t_camera *camera);

int						parser(char *filename, t_scene *scene);

/* PARSER FUNCTIONS */
void					parse_ambient_light(char **args, t_scene *scene);
void					parse_camera(char **args, t_scene *scene);
void					parse_light(char **args, t_scene *scene);
void					parse_sphere(char **args, t_scene *scene, int has_texture);
void					parse_plane(char **args, t_scene *scene, int has_texture);
void					parse_cylinder(char **args, t_scene *scene, int has_texture);
void					parse_cone(char **args, t_scene *scene, int has_texture);

/* DEBUG FUNCTIONS */
void					debug_map(t_map *map);
void					debug_scene(t_scene *scene);
void					debug_camera(t_camera *cam);
void					debug_ambient(t_amb_light *amb);
void					debug_light(t_light *light);
void					debug_objects(t_stack *objects);
void					debug_lights(t_stack *lights);
void					debug_vec(char *name, t_vec v);
void					debug_color(char *name, t_color c);
void					debug_sphere(t_sphere *s);
void					debug_plane(t_plane *p);
void					debug_cylinder(t_cylinder *c);
void					debug_object(t_object *obj);

/* Object functions */
t_sphere *create_sphere(char **args);
t_object	*create_object(int obj_type, void *object, size_t id, char *texture_path[2]);
t_plane *create_plane(char **args);
t_cylinder *create_cylinder(char **args);
t_cone *create_cone(char **args);


/* Texture functions */
int   load_texture(t_object *object);
t_color textures_handler(t_hit *hit, t_scene *scene);

/* Cache functions */
void					init_cache(t_scene *scene);
int						add_pixel_to_cache(t_obj_cache *cache, int x, int y);
void					clear_cache(t_scene *scene);
void					free_cache(t_scene *scene);

/* FREE FUCNTIONS */
void					free_map(t_map *map);
void					free_scene(t_scene *scene);
void	free_sphere(void *sphere);
void	free_cylinder(void *sphere);
void	free_plane(void *sphere);
void	free_cone(void *cone);
void	free_object(void *object);

/* MLX HOOKS */
void					custom_key_hook(mlx_key_data_t keydata, void *param);
void	object_selector_hook(int32_t x, int32_t y, modifier_key_t mods, t_hook_data *data);
void	custom_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *data);


int    rotate_object(mlx_key_data_t keydata, t_hook_data *data);
int    move_object(mlx_key_data_t keydata, t_hook_data *data);
int    resize_object(mlx_key_data_t keydata, t_hook_data *data);

void select_object(t_scene *scene, t_object *object, mlx_image_t *image);
void deselect_object(t_scene *scene, t_object *object, mlx_image_t *image);

void	resize_helper(t_object *obj, int is_bigger);
void	move_helper(t_object *obj, double x_val, double y_val);
void	clamp_orientation(t_vec *orientation);
void	brighten_pixel(mlx_image_t *image, uint32_t x, uint32_t y);
void	restore_pixel(t_scene *scene, mlx_image_t *image, uint32_t x, uint32_t y);

void get_cylinder_normal(t_hit *hit,t_object *obj, t_cylinder *cyl, t_ray ray);
int hit_cylinder(t_ray ray,t_object *obj, t_cylinder *cyl, double *obj_distance);


#endif