/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:37 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/14 19:02:34 by jgomez-d         ###   ########.fr       */
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

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
	
}	t_vector;

typedef struct s_color
{
	unsigned char 		r; 
	unsigned char 		g;
	unsigned char 		b;

}	t_color; // [0-255]

typedef struct s_rayo
{
	long 		origin;
	long 		direction;

}	t_rayo;

typedef struct s_amb_light
{
	t_color		*amb_col; 
	float		amb_ratio;		// [0.0,1.0]

}	t_amb_light;

typedef struct s_camera
{
	t_vector	*view_point;
	t_vector	*vector; 		// [-1,1]
	long		fov;			// [0,180]

}	t_camera;

typedef struct s_light
{
	t_vector	*light_point;
	float		brightness;		// [0.0,1.0]
	t_color		*color_range;	// BONUS

}	t_light;

typedef struct s_sphere
{
	t_vector	*center;
	float 		diameter;
	t_color		*color_range; 

}	t_sphere;

typedef struct s_plane
{
	t_vector	*point;
	t_vector	*vector;		 // [-1,1]
	t_color		*color_range;

}	t_plane;

typedef struct s_cylinder
{
	t_vector	*center;
	t_vector	*axys; 		// [-1,1]
	t_color		*color_range;
	float 		diameter;
	float 		height;

}	t_cylinder;

typedef struct s_map
{
	t_camera	*camera;
	t_stack		*planes;
	t_stack		*cylinders;
	t_stack		*spheres;
	t_light		*light;
	t_amb_light	*amb_ligt;
}	t_map;


void	exit_error(char *err_msg, void *free_data);

/* VECTOR UTILS - src/utils/vector.c */
int ft_str_is_vector(char *str);
t_vector	*create_vector(char *vector_str);
int is_normalized_vec(t_vector *vector);

/* COLOR UTILS - src/utils/color.c */
int ft_str_is_color(char *str);
t_color	*create_color(char *color_str);

t_map	*init_map();


t_map	*parser(char *filename);
void	debug_map(t_map *map);

/* FREE FUCNTIONS */
void	free_map(t_map *map);


#endif 
