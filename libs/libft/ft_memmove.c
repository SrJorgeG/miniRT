/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:00 by dcid-san          #+#    #+#             */
/*   Updated: 2024/10/04 04:30:24 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sc;
	size_t			i;

	if (!dest || !src)
		return (NULL);
	dst = (unsigned char *) dest;
	sc = (unsigned char *) src;
	if (dest < src + n && dest > src)
	{
		i = n + 1;
		while (i-- && i >= 1)
			dst[i - 1] = sc[i - 1];
	}
	else
	{
		i = -1;
		while (++i < n)
			dst[i] = sc[i];
	}
	return (dest);
}
