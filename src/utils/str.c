/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:44:47 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:49 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static size_t	ft_findchr(char const *s, char c[2])
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c[0] && s[i] != c[1])
		i++;
	return (i);
}

static size_t	ft_count_words(char const *s, char c[2])
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c[0] || *s == c[1])
		{
			if (in_word)
			{
				count++;
				in_word = 0;
			}
		}
		else
			in_word = 1;
		s++;
	}
	if (in_word)
		count++;
	return (count);
}

static void	ft_copy_word(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	ft_assign_word(char ***list, const char **s, char c[2], size_t index)
{
	size_t	wordsize;

	while (**s && (**s == c[0] || **s == c[1]))
		(*s)++;
	wordsize = ft_findchr(*s, c);
	(*list)[index] = malloc((wordsize + 1) * sizeof(char));
	if ((*list)[index] == NULL)
		return (0);
	ft_copy_word((*list)[index], *s, wordsize);
	*s += wordsize;
	return (1);
}

char	**ft_split_2(char const *s, char c[2])
{
	size_t	words;
	size_t	i;
	char	**list;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	list = malloc((words + 1) * sizeof(char *));
	if (list == NULL)
		return (NULL);
	list[words] = NULL;
	i = 0;
	while (i < words)
	{
		if (!ft_assign_word(&list, &s, c, i))
		{
			while (i > 0)
				free(list[--i]);
			free(list);
			return (NULL);
		}
		i++;
	}
	return (list);
}
