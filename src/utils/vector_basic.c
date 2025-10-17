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
t_vector	*vector_sum(t_vector *v1, t_vector *v2)
{
	t_vector	*sum;
	
	sum = malloc(sizeof(t_vector));
	if (!sum)
		return (NULL);
	sum->x = v1->x + v2->x;
	sum->y = v1->y + v2->y;
	sum->z = v1->z + v2->z;
	return (sum);
}

// RESTA DE DOS VECTORES
t_vector	*vector_rest(t_vector *v1, t_vector *v2)
{
	t_vector	*rest;
	
	rest = malloc(sizeof(t_vector));
	if (!rest)
		return (NULL);
	rest->x = v1->x - v2->x;
	rest->y = v1->y - v2->y;
	rest->z = v1->z - v2->z;
	return (rest);
}

// MULTIPLICACION DE UN VECTOR POR UN ESCALAR
t_vector	*vector_multiplication(t_vector *v1, long num)
{
	t_vector	*mult;
	
	mult = malloc(sizeof(t_vector));
	if (!mult)
		return (NULL);
	mult->x = v1->x * num;
	mult->y = v1->y * num;
	mult->z = v1->z * num;
	return (mult);
}

// DIVISION DE UN VECTOR POR UN ESCALAR
t_vector	*vector_division(t_vector *v1, long num)
{
	t_vector	*div;
	
	div = malloc(sizeof(t_vector));
	if (!div)
		return (NULL);
	div->x = v1->x / num;
	div->y = v1->y / num;
	div->z = v1->z / num;
	return (div);
}

// DUPLICADOR DE VECTOR (puede no ser usado)
t_vector	*vector_dup(t_vector *vec)
{
	t_vector	*dup;
	
	dup = malloc(sizeof(t_vector));
	if (!dup)
		return (NULL);
	dup->x = vec->x;
	dup->y = vec->y;
	dup->z = vec->z;
	return (dup);
}