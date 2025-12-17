/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_trans.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 01:34:27 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/12/17 03:09:39 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEO_TRANS_H
# define GEO_TRANS_H

# include <math.h>
typedef struct s_vector t_vec;
// Vector 4D (homogéneo) - para multiplicar con matrices 4x4
typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

// Matriz 4x4 (fila-columna)
typedef struct s_mat4
{
	float	m[4][4];
}	t_mat4;

/* ========================================================================== */
/*                      FUNCIONES DE MATRICES BÁSICAS                         */
/* ========================================================================== */

// Crear matriz identidad
t_mat4	mat4_identity(void);

// Multiplicación de matrices
t_mat4	mat4_multiply(t_mat4 a, t_mat4 b);

// Multiplicar matriz por vector
t_vec4	mat4_multiply_vec4(t_mat4 m, t_vec4 v);
t_vec	mat4_multiply_vec3(t_mat4 m, t_vec v);

// Matriz inversa (para transformaciones inversas)
t_mat4	mat4_inverse(t_mat4 m);

// Transpuesta
t_mat4	mat4_transpose(t_mat4 m);

/* ========================================================================== */
/*                    TRANSFORMACIONES GEOMÉTRICAS                            */
/* ========================================================================== */

// TRASLACIÓN: Mover objeto en el espacio
t_mat4	mat4_translate(float x, float y, float z);
t_mat4	mat4_translate_vec(t_vec v);

// ESCALADO: Cambiar tamaño del objeto
t_mat4	mat4_scale(float x, float y, float z);
t_mat4	mat4_scale_uniform(float s);

// ROTACIÓN: Girar objeto alrededor de un eje
t_mat4	mat4_rotate_x(float angle_rad);
t_mat4	mat4_rotate_y(float angle_rad);
t_mat4	mat4_rotate_z(float angle_rad);

// Rotación alrededor de un eje arbitrario
t_mat4	mat4_rotate_axis(t_vec axis, float angle_rad);

// TRANSFORMACIÓN COMPUESTA: Para aplicar varias transformaciones
t_mat4	mat4_transform(t_vec translation, t_vec rotation, t_vec scale);

t_mat4	mat4_transpose(t_mat4 m);

t_mat4	mat4_inverse(t_mat4 m);

t_vec  mat4_transform_point(t_mat4 m, t_vec p);

t_vec  mat4_transform_direction(t_mat4 m, t_vec d);

t_vec  mat4_transform_normal(t_mat4 m, t_vec n);

void    build_orthonormal_basis(t_vec forward, t_vec *right, t_vec *up);

t_mat4  build_rotation_matrix(t_vec right, t_vec up, t_vec forward);

t_mat4  cylinder_build_transform(t_vec center, t_vec axis, float height);

#endif