/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-01 01:37:59 by dcid-san          #+#    #+#             */
/*   Updated: 2025-04-01 01:37:59 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort_int(int *lst, int size)
{
	int	wrapper;
	int	i;

	i = 0;
	while (i < (size - 1))
	{
		if (lst[i] > lst[i + 1])
		{
			wrapper = lst[i];
			lst[i] = lst[i + 1];
			lst[i + 1] = wrapper;
			i = 0;
		}
		else
			i++;
	}
}
