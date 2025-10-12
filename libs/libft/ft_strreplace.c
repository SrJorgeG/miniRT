/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 09:28:45 by dcid-san          #+#    #+#             */
/*   Updated: 2025/09/11 09:54:48 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	copy_prefix(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (i);
}

static size_t	copy_str(char *dst, const char *src, size_t pos)
{
	size_t	j;

	j = 0;
	while (src[j])
	{
		dst[pos + j] = src[j];
		j++;
	}
	return (pos + j);
}

/*
** Replaces [start, end) in str with rep.
** Returns malloc'd new string.
*/
char	*ft_strreplace(const char *str, size_t start,
			size_t end, const char *rep)
{
	size_t	len;
	char	*new;
	size_t	pos;

	if (!str || start > end || end > ft_strlen(str))
		return (NULL);
	if (!rep)
		rep = "";
	len = start + ft_strlen(rep) + ft_strlen(str + end);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	pos = copy_prefix(new, str, start);
	pos = copy_str(new, rep, pos);
	pos = copy_str(new, str + end, pos);
	new[pos] = '\0';
	return (new);
}
