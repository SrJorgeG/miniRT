/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:09 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/23 19:51:58 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*swrap;
	unsigned char	cwrap;

	swrap = (unsigned char *)s;
	cwrap = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (swrap[i] == cwrap)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
