/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:02 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/23 19:52:29 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	wrap;
	unsigned char	*ptr_wrap;

	i = 0;
	ptr_wrap = (unsigned char *)s;
	wrap = (unsigned char) c;
	while (i < n)
	{
		ptr_wrap[i] = wrap;
		i++;
	}
	return (s);
}
