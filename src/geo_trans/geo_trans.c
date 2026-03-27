/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geo_trans.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 01:28:48 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/12/18 19:29:02 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/geo_trans.h"
#include <string.h>

/* ========================================================================== */
/*              CONVERSIÓN ENTRE VEC3 Y VEC4                                  */
/* ========================================================================== */

// Convertir vec3 a vec4 (añadiendo componente w)
t_vec4  vec3_to_vec4(t_vec v, float w)
{
    t_vec4  result;

    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    result.w = w;
    
    return (result);
}

// Convertir vec4 a vec3 (dividiendo por w si es necesario)
t_vec  vec4_to_vec3(t_vec4 v)
{
    t_vec  result;

    // Normalización homogénea: dividir por w
    if (v.w != 0.0f && v.w != 1.0f)
    {
        result.x = v.x / v.w;
        result.y = v.y / v.w;
        result.z = v.z / v.w;
    }
    else
    {
        result.x = v.x;
        result.y = v.y;
        result.z = v.z;
    }
    
    return (result);
}

/* ========================================================================== */
/*                           MATRIZ IDENTIDAD                                 */
/* ========================================================================== */

t_mat4	mat4_identity(void)
{
	t_mat4	m;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i == j)
				m.m[i][j] = 1.0f;
			else
				m.m[i][j] = 0.0f;
			j++;
		}
		i++;
	}
	return (m);
}

/* ========================================================================== */
/*                      MULTIPLICACIÓN DE MATRICES                            */
/* ========================================================================== */

t_mat4	mat4_multiply(t_mat4 a, t_mat4 b)
{
	t_mat4	result;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = 0.0f;
			k = 0;
			while (k < 4)
			{
				result.m[i][j] += a.m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}

/* ========================================================================== */
/*                  MULTIPLICACIÓN MATRIZ x VECTOR                            */
/* ========================================================================== */

t_vec4	mat4_multiply_vec4(t_mat4 m, t_vec4 v)
{
	t_vec4	result;

	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return (result);
}

t_vec	mat4_multiply_vec3(t_mat4 m, t_vec v)
{
	t_vec4	v4;
	t_vec4	result;

	v4 = vec3_to_vec4(v, 1.0f);
	result = mat4_multiply_vec4(m, v4);
	return (vec4_to_vec3(result));
}

/* ========================================================================== */
/*                           TRASLACIÓN                                       */
/* ========================================================================== */

t_mat4	mat4_translate(float x, float y, float z)
{
	t_mat4	m;

	m = mat4_identity();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

t_mat4	mat4_translate_vec(t_vec v)
{
	return (mat4_translate(v.x, v.y, v.z));
}

/* ========================================================================== */
/*                              ESCALADO                                      */
/* ========================================================================== */

t_mat4	mat4_scale(float x, float y, float z)
{
	t_mat4	m;

	m = mat4_identity();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return (m);
}

t_mat4	mat4_scale_uniform(float s)
{
	return (mat4_scale(s, s, s));
}

/* ========================================================================== */
/*                         ROTACIÓN EJE X                                     */
/* ========================================================================== */

t_mat4	mat4_rotate_x(float angle_rad)
{
	t_mat4	m;
	float	c;
	float	s;

	m = mat4_identity();
	c = cosf(angle_rad);
	s = sinf(angle_rad);
	m.m[1][1] = c;
	m.m[1][2] = -s;
	m.m[2][1] = s;
	m.m[2][2] = c;
	return (m);
}

/* ========================================================================== */
/*                         ROTACIÓN EJE Y                                     */
/* ========================================================================== */

t_mat4	mat4_rotate_y(float angle_rad)
{
	t_mat4	m;
	float	c;
	float	s;

	m = mat4_identity();
	c = cosf(angle_rad);
	s = sinf(angle_rad);
	m.m[0][0] = c;
	m.m[0][2] = s;
	m.m[2][0] = -s;
	m.m[2][2] = c;
	return (m);
}

/* ========================================================================== */
/*                         ROTACIÓN EJE Z                                     */
/* ========================================================================== */

t_mat4	mat4_rotate_z(float angle_rad)
{
	t_mat4	m;
	float	c;
	float	s;

	m = mat4_identity();
	c = cosf(angle_rad);
	s = sinf(angle_rad);
	m.m[0][0] = c;
	m.m[0][1] = -s;
	m.m[1][0] = s;
	m.m[1][1] = c;
	return (m);
}

/* ========================================================================== */
/*                   ROTACIÓN ALREDEDOR DE EJE ARBITRARIO                     */
/*   Fórmula de Rodrigues                                                     */
/* ========================================================================== */

t_mat4	mat4_rotate_axis(t_vec axis, float angle_rad)
{
	t_mat4	m;
	t_vec	a;
	float	c;
	float	s;
	float	t;

	a = vector_normalize(axis);
	c = cosf(angle_rad);
	s = sinf(angle_rad);
	t = 1.0f - c;
	
	m = mat4_identity();
	m.m[0][0] = t * a.x * a.x + c;
	m.m[0][1] = t * a.x * a.y - s * a.z;
	m.m[0][2] = t * a.x * a.z + s * a.y;
	
	m.m[1][0] = t * a.x * a.y + s * a.z;
	m.m[1][1] = t * a.y * a.y + c;
	m.m[1][2] = t * a.y * a.z - s * a.x;
	
	m.m[2][0] = t * a.x * a.z - s * a.y;
	m.m[2][1] = t * a.y * a.z + s * a.x;
	m.m[2][2] = t * a.z * a.z + c;
	
	return (m);
}

/* ========================================================================== */
/*                   TRANSFORMACIÓN COMPUESTA (TRS)                           */
/*   Orden: Primero escala, luego rota, luego traslada                        */
/* ========================================================================== */

t_mat4	mat4_transform(t_vec translation, t_vec rotation, t_vec scale)
{
	t_mat4	t_mat;
	t_mat4	r_mat;
	t_mat4	s_mat;
	t_mat4	result;

	// Crear matrices individuales
	t_mat = mat4_translate_vec(translation);
	r_mat = mat4_rotate_z(rotation.z);
	r_mat = mat4_multiply(mat4_rotate_y(rotation.y), r_mat);
	r_mat = mat4_multiply(mat4_rotate_x(rotation.x), r_mat);
	s_mat = mat4_scale(scale.x, scale.y, scale.z);
	
	// Multiplicar: T * R * S
	result = mat4_multiply(r_mat, s_mat);
	result = mat4_multiply(t_mat, result);
	
	return (result);
}

/* ========================================================================== */
/*                          TRANSPUESTA                                       */
/* ========================================================================== */

t_mat4	mat4_transpose(t_mat4 m)
{
	t_mat4	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.m[i][j] = m.m[j][i];
			j++;
		}
		i++;
	}
	return (result);
}

/* ========================================================================== */
/*                      MATRIZ INVERSA (simplificada)                         */
/*   Para transformaciones de rotación y traslación (matrices ortogonales)    */
/* ========================================================================== */

t_mat4	mat4_inverse(t_mat4 m)
{
	t_mat4	inv;

	// Esta es una implementación simplificada para matrices de transformación
	// Para una inversa completa necesitarías el método de Gauss-Jordan
	// o calcular la adjunta y determinante
	
	// Transponer la parte de rotación (3x3)
	inv = mat4_transpose(m);
	
	// Invertir la traslación
	inv.m[0][3] = -(m.m[0][3] * inv.m[0][0] + m.m[1][3] * inv.m[0][1] + m.m[2][3] * inv.m[0][2]);
	inv.m[1][3] = -(m.m[0][3] * inv.m[1][0] + m.m[1][3] * inv.m[1][1] + m.m[2][3] * inv.m[1][2]);
	inv.m[2][3] = -(m.m[0][3] * inv.m[2][0] + m.m[1][3] * inv.m[2][1] + m.m[2][3] * inv.m[2][2]);
	
	return (inv);
}
/* ========================================================================== */
/*              TRANSFORMAR UN PUNTO (w = 1)                                  */
/*   Los puntos se ven afectados por traslación, rotación y escalado         */
/* ========================================================================== */

t_vec  mat4_transform_point(t_mat4 m, t_vec p)
{
    t_vec  result;
    float   w;

    // Multiplicar como si fuera un vector 4D con w=1
    result.x = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2] * p.z + m.m[0][3];
    result.y = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2] * p.z + m.m[1][3];
    result.z = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2] * p.z + m.m[2][3];
    w = m.m[3][0] * p.x + m.m[3][1] * p.y + m.m[3][2] * p.z + m.m[3][3];
    
    // Dividir por w (normalización homogénea)
    if (w != 1.0f && w != 0.0f)
    {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }
    
    return (result);
}

/* ========================================================================== */
/*            TRANSFORMAR UNA DIRECCIÓN (w = 0)                               */
/*   Las direcciones NO se ven afectadas por traslación                      */
/*   Solo se aplica rotación y escalado                                      */
/* ========================================================================== */

t_vec  mat4_transform_direction(t_mat4 m, t_vec d)
{
    t_vec  result;

    // Multiplicar como si fuera un vector 4D con w=0
    // (ignora la columna de traslación m[i][3])
    result.x = m.m[0][0] * d.x + m.m[0][1] * d.y + m.m[0][2] * d.z;
    result.y = m.m[1][0] * d.x + m.m[1][1] * d.y + m.m[1][2] * d.z;
    result.z = m.m[2][0] * d.x + m.m[2][1] * d.y + m.m[2][2] * d.z;
    
    return (result);
}

/* ========================================================================== */
/*              TRANSFORMAR UNA NORMAL (especial)                             */
/*   Las normales se transforman con la TRANSPUESTA de la INVERSA            */
/*   Esto mantiene la perpendicularidad correcta                             */
/* ========================================================================== */

t_vec  mat4_transform_normal(t_mat4 m, t_vec n)
{
    t_mat4  inverse_transpose;
    t_vec  result;
    
    // Para normales, necesitas (M⁻¹)ᵀ
    // Si ya tienes la inversa, solo transpón
    inverse_transpose = mat4_transpose(m);
    
    // Transformar como dirección
    result = mat4_transform_direction(inverse_transpose, n);
    
    // Normalizar el resultado
    return (vector_normalize(result));
}
/* ========================================================================== */
/*          CONSTRUIR BASE ORTONORMAL DESDE UN EJE                            */
/*                                                                            */
/*   Dado un eje (forward), construye dos vectores perpendiculares           */
/*   para formar una base ortonormal (right, up, forward)                    */
/* ========================================================================== */

void    build_orthonormal_basis(t_vec forward, t_vec *right, t_vec *up)
{
    t_vec  temp_up;

    // Normalizar el eje forward
    forward = vector_normalize(forward);

    // Elegir un vector temporal que NO sea paralelo a forward
    // Si forward apunta principalmente en Y, usar X como referencia
    if (fabs(forward.y) < 0.99f)
        temp_up = (t_vec){0, 1, 0};
    else
        temp_up = (t_vec){1, 0, 0};

    // Calcular right (perpendicular a forward y temp_up)
    *right = vector_cross_prod(temp_up, forward);
    *right = vector_normalize(*right);

    // Calcular up (perpendicular a forward y right)
    *up = vector_cross_prod(forward, *right);
    // No hace falta normalizar, ya es ortonormal
}

/* ========================================================================== */
/*        CONSTRUIR MATRIZ DE ROTACIÓN DESDE BASE ORTONORMAL                 */
/*                                                                            */
/*   Construye una matriz de rotación que alinea el eje Y canónico           */
/*   con el eje dado (forward)                                               */
/* ========================================================================== */

t_mat4  build_rotation_matrix(t_vec right, t_vec up, t_vec forward)
{
    t_mat4  m;

    m = mat4_identity();

    // Las columnas de la matriz son los vectores de la base
    // Primera columna = right (eje X local)
    m.m[0][0] = right.x;
    m.m[1][0] = right.y;
    m.m[2][0] = right.z;

    // Segunda columna = up (eje Y local = nuestro eje del cilindro)
    m.m[0][1] = forward.x;
    m.m[1][1] = forward.y;
    m.m[2][1] = forward.z;

    // Tercera columna = forward (eje Z local)
    m.m[0][2] = up.x;
    m.m[1][2] = up.y;
    m.m[2][2] = up.z;

    return (m);
}

/* ========================================================================== */
/*              FUNCIÓN PRINCIPAL: cylinder_build_transform                   */
/*                                                                            */
/*   Construye la matriz de transformación completa para un cilindro         */
/*   Orden: Traslación * Rotación                                            */
/*                                                                            */
/*   El cilindro canónico está en el origen con eje Y                        */
/*   Esta matriz lo mueve a 'center' y lo rota hacia 'axis'                  */
/* ========================================================================== */

t_mat4  cylinder_build_transform(t_vec center, t_vec axis, float height)
{
    t_mat4  translate;
    t_mat4  rotate;
    t_mat4  result;
    t_vec  right;
    t_vec  up;
	(void)height;
	
    // 1. Construir base ortonormal desde el eje
    build_orthonormal_basis(axis, &right, &up);

    // 2. Construir matriz de rotación
    rotate = build_rotation_matrix(right, up, axis);

    // 3. Construir matriz de traslación
    translate = mat4_translate(center.x, center.y, center.z);

    // 4. Combinar: Traslación * Rotación
    // IMPORTANTE: El orden importa!
    result = mat4_multiply(translate, rotate);

    return (result);
}