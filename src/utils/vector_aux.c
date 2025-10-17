/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:58:42 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/17 15:29:00 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// DEVUELVE LA LONGITUD AL CUADRADO DE UN VECTOR
inline double	vector_lenght_square(t_vector *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

// DEVUELVE LA LONGITUD DE UN VECTOR
inline double	vector_lenght(t_vector *vec)
{
	return (sqrt(vector_lenght_square(vec)));
}

// DEVUELVE UN VECTOR NORMALIZADO
t_vector	*vector_normalize(t_vector *vec)
{
	t_vector	*vector;
	double		len;
	
	len = lenght(vec);
	if (!len)
		return (NULL);
	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = vec->x / len;
	vector->y = vec->y / len;
	vector->z = vec->z / len;
	return (vector);
}

// DEVUELVE EL DOT PRODUCT 
// (La suma de las tres coordenadas de ambos vectores multiplicadas)
double		vector_dot_prod(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);	
}

// DEVUELVE EL CROSS PRODUCT DE DOS VECTORES
t_vector	*vector_cross_prod(t_vector *v1, t_vector *v2)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = v1->y * v2->z - v1->z * v2->y;
	vector->y = v1->z * v2->x - v1->x * v2->z;
	vector->z =	v1->x * v2->y - v1->y * v2->x;
	return (vector);
}
