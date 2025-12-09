/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:37 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/19 16:48:48 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINIRT_H)
#define MINIRT_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
#include <stdlib.h>
#include <memory.h>
/* 				MLX DEFINES			 */
#define HEIGHT 800
#define WIDTH 800
#define TITLE "MiniRT - De tu padre"

# define RAY_T_MIN 0.0001f
# define RAY_T_MAX 1.0e30f
#define FOCAL 1
typedef double t_real;

typedef enum e_object_type
{
    SPHERE,
    PLANE,
    CYLINDER
} t_object_type;


typedef struct s_vector
{
	double		x;
	double		y;
	double		z;

}	t_vec;


typedef struct s_vector t_point;
typedef struct s_color
{
	unsigned char 		r;
	unsigned char 		g;
	unsigned char 		b;

}	t_color; // [0-255]

typedef struct s_ray
{
	t_vec       origin;
	t_vec       direction;

}	t_ray;

typedef struct s_amb_light
{
	t_color		amb_col;
	float		amb_ratio;		// [0.0,1.0]

}	t_amb_light;

typedef struct s_camera
{
	t_vec	    view_point;
	t_vec	    orientation_nor;
	t_vec	    right;
	t_vec	    up;
	int		        fov;
	unsigned int	focal;
	double          radial_fov;

}	t_camera;

typedef struct s_light
{
	t_vec	light_point;
	float		brightness;		// [0.0,1.0]
	t_color		color_range;	// BONUS

}	t_light;

typedef struct s_sphere
{
	t_vec		center;
	double 		diameter;
	double 		radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec	point;
	t_vec	vector;		 // [-1,1]
}	t_plane;

typedef struct s_cylinder
{
	t_vec	center;
	t_vec	axys; 		// [-1,1]
	double 		diameter;
	double 		height;

}	t_cylinder;


typedef struct s_object
{
    t_object_type	type;
    void		*object;
    t_color		color_range;
}	t_object;

typedef struct s_map
{
	t_camera	camera;
	t_stack		*objects;
	t_object	*last_hit;
	t_stack		*lights;
	t_amb_light	amb_ligt;
}	t_map;

typedef struct s_scene
{
    t_real  aspect;
    t_real  viewport;
    t_map   map;
    int     screen_w;
    int     screen_h;
    t_real  viewport_w;
    t_real  viewport_h;
} t_scene;

/* Struct usado para guardar informacion del choque de un t_ray */
typedef struct s_hit
{
    int			hit;          // 1 si hubo choque, 0 si no
    double 		t;            // La distancia al punto de choque
    t_vec  		p;            // El punto exacto de la intersección (P = Origen + t * Dirección)
    t_vec  		normal;       // La normal de la superficie en el punto 'p'
    t_color		color;        // El color del objeto golpeado
    t_object	*object;
} t_hit;

void	exit_error(char *err_msg, void *free_data);

/* VECTOR UTILS - src/utils/vector.c */
int ft_str_is_vector(char *str);
t_vec	create_vector(char *vector_str);
int is_normalized_vec(t_vec *vector);
t_vec	*vector_constructor(double x, double y, double z);
void	vector_destructor(t_vec	*vector);

/* VECTOR_BASIC - src/utils/vector_basic.c */
t_vec	vector_sum(t_vec v1, t_vec v2);
t_vec	vector_rest(t_vec v1, t_vec v2);
t_vec	vector_multiplication(t_vec v1, double num);
t_vec	vector_division(t_vec v1, double num);
t_vec	*vector_dup(t_vec vec);

/* VECTOR_AUX - src/utils/vector_aux.c */
double	vector_lenght_square(t_vec *vec);
double	vector_lenght(t_vec *vec);
t_vec	vector_normalize(t_vec vec);
double		vector_dot_prod(t_vec v1, t_vec v2);
t_vec	vector_cross_prod(t_vec v1, t_vec v2);

/*	 Hit functionss 	*/
int	hit_sphere(t_ray ray, t_sphere *sphere, double *obj_distance);

/* COLOR UTILS - src/utils/color.c */
int ft_str_is_color(char *str);

u_int8_t	create_color(char *color_str, t_color *color);

t_color color_multiply(t_color c1, t_color c2);
t_color color_scale(t_color c, double factor);
t_color color_add(t_color c1, t_color c2);
t_color color_clamp(t_color c);



t_map	*init_map();


t_map	*parser(char *filename);
void	debug_map(t_map *map);

/* FREE FUCNTIONS */
void	free_map(t_map *map);


#endif
