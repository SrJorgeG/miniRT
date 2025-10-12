/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:14:51 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/24 18:25:37 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	if (!*little)
		return ((char *)big);
	x = 0;
	while (x < len && big[x])
	{
		y = 0;
		while (big [x + y] == little[y] && (x + y < len))
		{
			y++;
			if (little[y] == '\0')
				return ((char *)(big + x));
		}
		x++;
	}
	return (NULL);
}
