/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:14:48 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/24 18:41:13 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c_wrap;
	char			*last;

	last = NULL;
	c_wrap = (unsigned char)c;
	while (*s)
	{
		if (*s == c_wrap)
			last = (char *) s;
		s++;
	}
	if (*s == c_wrap)
		return ((char *)s);
	return (last);
}
