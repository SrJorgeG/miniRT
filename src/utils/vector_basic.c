/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:34:34 by jgomez-d          #+#    #+#             */
/*   Updated: 2025/10/17 21:47:56 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// SUMA DE DOS VECTORES
//t_vec	*vector_sum(t_vec *v1, t_vec *v2)
//{
//	t_vec	*sum;
//
//	sum = malloc(sizeof(t_vec));
//	if (!sum)
//		return (NULL);
//	sum->x = v1->x + v2->x;
//	sum->y = v1->y + v2->y;
//	sum->z = v1->z + v2->z;
//	return (sum);
//}

t_vec	vector_sum(t_vec v1, t_vec v2)
{
	return ((t_vec) {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec	vector_rest(t_vec v1, t_vec v2)
{
	return ((t_vec) {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}
// RESTA DE DOS VECTORES
//t_vec	*vector_rest(t_vec *v1, t_vec *v2)
//{
//	t_vec	*rest;
//
//	rest = malloc(sizeof(t_vec));
//	if (!rest)
//		return (NULL);
//	rest->x = v1->x - v2->x;
//	rest->y = v1->y - v2->y;
//	rest->z = v1->z - v2->z;
//	return (rest);
//}

// MULTIPLICACION DE UN VECTOR POR UN ESCALAR
//t_vec	*vector_multiplication(t_vec *v1, long num)
//{
//	t_vec	*mult;
//
//	mult = malloc(sizeof(t_vec));
//	if (!mult)
//		return (NULL);
//	mult->x = v1->x * num;
//	mult->y = v1->y * num;
//	mult->z = v1->z * num;
//	return (mult);
//}

t_vec	vector_multiplication(t_vec *v1, double num)
{
    return ((t_vec) {v1->x * num, v1->y * num, v1->z * num});
}

t_vec	vector_division(t_vec *v1, double num)
{
    return ((t_vec) {v1->x * num, v1->y * num, v1->z * num});
}
// DIVISION DE UN VECTOR POR UN ESCALAR
//t_vec	vector_division(t_vec *v1, long num)
//{
//	t_vec	*div;
//
//	div = malloc(sizeof(t_vec));
//	if (!div)
//		return (NULL);
//	div->x = v1->x / num;
//	div->y = v1->y / num;
//	div->z = v1->z / num;
//	return (div);
//}

// DUPLICADOR DE VECTOR (puede no ser usado)
t_vec	*vector_dup(t_vec vec)
{
	t_vec	*dup;

	dup = malloc(sizeof(t_vec));
	if (!dup)
		return (NULL);
	dup->x = vec.x;
	dup->y = vec.y;
	dup->z = vec.z;
	return (dup);
}
