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

static size_t	ft_findchr(const char *s, char c[2])
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c[0] && s[i] != c[1])
		i++;
	return (i);
}

static size_t	ft_count_words(const char *s, char c[2])
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c[0] && *s != c[1])
		{
			cnt++;
			while (*s && *s != c[0] && *s != c[1])
				s++;
		}
		else
			s++;
	}
	return (cnt);
}

static void	ft_copy_word(char *d, const char *s, size_t l)
{
	while (l--)
		*d++ = *s++;
	*d = '\0';
}

char	**ft_split_2(const char *s, char c[2])
{
	char	**res;
	size_t	cnt;
	size_t	i;
	size_t	sz;

	if (!s)
		return (NULL);
	cnt = ft_count_words(s, c);
	res = malloc((cnt + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	res[cnt] = NULL;
	i = 0;
	while (i < cnt)
	{
		while (*s == c[0] || *s == c[1])
			s++;
		sz = ft_findchr(s, c);
		res[i] = malloc(sz + 1);
		if (!res[i])
			return (free(res), NULL);
		ft_copy_word(res[i++], s, sz);
		s += sz;
	}
	return (res);
}
