/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:30:17 by jgomez-d         #+#    #+#             */
/*   Updated: 2025/10/17 15:30:17 by jgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	ft_str_is_vector(char *str)
{
	int	component_count;
	int	digit_len;

	component_count = 0;
	digit_len = 0;
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str))
			digit_len++;
		else if (*str == ',')
		{
			if (digit_len == 0 || component_count >= 2)
				return (0);
			component_count++;
			digit_len = 0;
		}
		else if (*str != '-' && *str != '+' && *str != '.')
			return (0);
		str++;
	}
	if (component_count == 2 && digit_len > 0)
		return (1);
	return (0);
}

int	vector_is_normalized(t_vec vector)
{
	if (vector.x < -1 || vector.x > 1)
		return (0);
	if (vector.y < -1 || vector.y > 1)
		return (0);
	if (vector.z < -1 || vector.z > 1)
		return (0);
	return (1);
}

int	is_normalized_vec(t_vec vector)
{
	if (vector.x < -1 || vector.x > 1)
		return (0);
	if (vector.y < -1 || vector.y > 1)
		return (0);
	if (vector.z < -1 || vector.z > 1)
		return (0);
	return (1);
}
