/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:48:37 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/09 14:36:50 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINIRT_H)
#define MINIRT_H


typedef struct s_coord
{
	long		x;
	long		y;
	long		z;

}	t_coord;

typedef struct s_vector
{
	long 		x;
	long 		y;
	long 		z;

}	t_vector;

typedef struct s_color
{
	long 		r; 
	long 		g;
	long 		b;

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
	t_coord		*view_point;
	t_vector	*vector; 		// [-1,1]
	long		fov;			// [0,180]

}	t_camera;

typedef struct s_light
{
	t_coord		*light_point;
	float		brightness;		// [0.0,1.0]
	t_color		*color_range;	// BONUS

}	t_light;

typedef struct s_sphere
{
	t_coord		*center;
	float 		diameter;
	t_color		*color_range; 

}	t_sphere;

typedef struct s_plane
{
	t_coord		*point;
	t_vector	*vector;		 // [-1,1]
	t_color		*color_range;

}	t_plane;

typedef struct s_cylinder
{
	t_coord		*point;
	t_vector	*vector; 		// [-1,1]
	t_color		*color_range;
	float 		diameter;
	float 		height;

}	t_cylinder;

#endif 
