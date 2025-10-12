/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:35:08 by dcid-san          #+#    #+#             */
/*   Updated: 2024/10/06 19:24:23 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static char	*fill_trimed(unsigned long len, char const *s1, char const *set)
{
	char	*trimedstr;

	if (len > 0)
	{
		len = len - 1;
		while (ft_strchr(set, s1[len]))
			len--;
		trimedstr = malloc(len + 2 * sizeof(char));
		if (trimedstr == NULL)
			return (NULL);
		ft_strlcpy(trimedstr, (char *)s1, len + 2);
	}
	else
	{
		trimedstr = malloc(sizeof(char));
		if (trimedstr == NULL)
			return (NULL);
		trimedstr[0] = '\0';
	}
	return (trimedstr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	int		i;

	i = -1;
	len = ft_strlen(s1);
	while (ft_strchr(set, s1[++i]) && s1[i])
		len--;
	s1 += i;
	return (fill_trimed(len, s1, set));
}

/* int main (void)
{
	//char *s1 = "  \t \t \n   \n\n\n\t";
	//char *s2 = "";
	char *ret = ft_strtrim("", "");
	printf("\nResponse:%s\n", ret);
	return (0);
} */