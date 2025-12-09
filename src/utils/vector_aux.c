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
inline double	vector_lenght_square(t_vec *vec)
{
	return (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

// DEVUELVE LA LONGITUD DE UN VECTOR
inline double	vector_lenght(t_vec *vec)
{
	return (sqrt(vector_lenght_square(vec)));
}

// DEVUELVE UN VECTOR NORMALIZADO
//t_vec	*vector_normalize(t_vec *vec)
//{
//	t_vec	*vector;
//
//	if (!len)
//		return (NULL);
//	vector = malloc(sizeof(t_vec));
//	if (!vector)
//		return (NULL);
//	vector->x = vec->x / len;
//	vector->y = vec->y / len;
//	vector->z = vec->z / len;
//	return (vector);
//}

t_vec vector_normalize(t_vec vec)
{
    double		len;

	len = vector_lenght(&vec);
    return ((t_vec) {vec.x / len, vec.y / len, vec.z / len});
}

// DEVUELVE EL DOT PRODUCT
// (La suma de las tres coordenadas de ambos vectores multiplicadas)
double		vector_dot_prod(t_vec *v1, t_vec *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

// DEVUELVE EL CROSS PRODUCT DE DOS VECTORES
//t_vec	*vector_cross_prod(t_vec *v1, t_vec *v2)
//{
//	t_vec	*vector;
//
//	vector = malloc(sizeof(t_vec));
//	if (!vector)
//		return (NULL);
//	vector->x = v1->y * v2->z - v1->z * v2->y;
//	vector->y = v1->z * v2->x - v1->x * v2->z;
//	vector->z =	v1->x * v2->y - v1->y * v2->x;
//	return (vector);
//}

t_vec	vector_cross_prod(t_vec *v1, t_vec *v2)
{
    return ((t_vec) {v1->y * v2->z - v1->z * v2->y,v1->z * v2->x - v1->x * v2->z, v1->x * v2->y - v1->y * v2->x });
}
