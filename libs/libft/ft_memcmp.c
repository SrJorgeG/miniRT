/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:07 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/25 12:54:44 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				res;
	unsigned char	*s1chr;
	unsigned char	*s2chr;
	size_t			i;

	i = -1;
	s1chr = (unsigned char *)s1;
	s2chr = (unsigned char *)s2;
	res = 0;
	while (res == 0 && ++i < n)
		res = s1chr[i] - s2chr[i];
	return (res);
}

/* #include <stdio.h>
int main (void)
{
	char *s1 = "atoms\0\0\0\0";
	char *s2 = "atoms\0abc";
	size_t size = 8;
	int res = ft_memcmp(s1, s2, size);
	printf("%d\n", res);
	return (0);
} */