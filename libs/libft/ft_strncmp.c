/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:14:53 by dcid-san          #+#    #+#             */
/*   Updated: 2024/10/06 19:05:38 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	iter;
	int		res;

	iter = 0;
	res = 0;
	while (res == 0 && iter < n && s1[iter] && s2[iter])
	{
		res = (unsigned char)s1[iter] - (unsigned char)s2[iter];
		iter++;
	}
	if (iter < n && ((s1[iter] == '\0' && s2[iter] != '\0') || (s1[iter] != '\0'
				&& s2[iter] == '\0')) && res == 0)
		res = (unsigned char)s1[iter] - (unsigned char)s2[iter];
	return (res);
}

/* #include <stdio.h>
int main ()
{
	char *s1 = "abcdef";
	char *s2 = "abcdefghijklmnop";
	printf("String1: %s\nString2: %s\n", s1, s2);
	printf("%d", ft_strncmp(s1,s2,6));
} */
