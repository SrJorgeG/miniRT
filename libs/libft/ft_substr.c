/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:42:37 by dcid-san          #+#    #+#             */
/*   Updated: 2024/10/06 19:55:07 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		slen;
	size_t		size;

	size = 0;
	if (!s)
		return (NULL);
	if (len != 0)
		size = len;
	slen = ft_strlen(s);
	if (start >= slen)
		size = 0;
	if (len > (slen - start))
		size = slen - start;
	substr = malloc((size + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, size + 1);
	return (substr);
}
