/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-01 15:53:22 by dcid-san          #+#    #+#             */
/*   Updated: 2025-04-01 15:53:22 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisdbl(char *str)
{
	int	dot;

	if (!str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	dot = 0;
	while (*str)
	{
		if ((!ft_isdigit(*str) && *str != '.')
			|| (*str == '.' && dot == 1))
			return (0);
		if (*str == '.')
			dot = 1;
		str++;
	}
	return (1);
}
