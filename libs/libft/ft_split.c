/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:37:57 by dcid-san          #+#    #+#             */
/*   Updated: 2025/06/03 23:19:31 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

/* This function returns th index of the first ocurrence of c in the string s*/
static size_t	ft_findchr(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t			count;
	unsigned int	add;

	count = 0;
	add = 0;
	while (*s)
	{
		if ((*s == c) && add)
		{
			count++;
			add = 0;
		}
		if (*s != c && !add)
			add = 1;
		s++;
	}
	if (add)
		count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	i;
	char	**list;
	size_t	wordsize;

	words = ft_count_words(s, c);
	list = malloc((words + 1) * sizeof(char *));
	if (list == NULL)
		return (NULL);
	list[words] = NULL;
	i = 0;
	wordsize = 0;
	while (i < words)
	{
		while (*s == c && *s)
			s++;
		wordsize = ft_findchr(s, c);
		list[i] = malloc((wordsize + 1) * sizeof(char));
		if (list[i] == NULL)
			return (NULL);
		ft_strncpy(list[i], s, wordsize + 1);
		s += wordsize + 1;
		i++;
	}
	return (list);
}
