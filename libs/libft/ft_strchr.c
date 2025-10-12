/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:14:48 by dcid-san          #+#    #+#             */
/*   Updated: 2024/10/01 03:30:42 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c_wrap;

	c_wrap = (unsigned char)c;
	while (*s)
	{
		if (*s == c_wrap)
			return ((char *)s);
		s++;
	}
	if (*s == c_wrap)
		return ((char *)s);
	return (NULL);
}
