/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:59:22 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/10 19:20:23 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_realloc(void *src, unsigned long oldsize, unsigned long newsize)
{
	unsigned char	*cpy;
	unsigned long	i;
	unsigned char	*srcchar;

	if (newsize == 0)
	{
		free(src);
		return (NULL);
	}
	i = 0;
	srcchar = (unsigned char *) src;
	cpy = (unsigned char *) malloc(newsize);
	if (src != NULL)
	{
		while (i < oldsize && i < newsize)
		{
			cpy[i] = srcchar[i];
			i++;
		}
	}
	free(src);
	return (cpy);
}

char	*ft_buffzero(char *buff)
{
	unsigned long	i;

	i = 0;
	while (buff[i])
	{
		buff[i] = '\0';
		i++;
	}
	return (buff);
}

unsigned long	ft_find_chr(char *str, char c, unsigned long size)
{
	unsigned long	i;

	i = 0;
	while (str[i] && i < size)
	{
		if (str[i] == c || str[i + 1] == '\0')
			break ;
		i++;
	}
	return (i);
}

/* char	*ft_strncpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;

	i = 0;
	while (i < (dsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
} */
