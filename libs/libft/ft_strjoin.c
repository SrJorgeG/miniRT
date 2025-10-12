/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:22:01 by dcid-san          #+#    #+#             */
/*   Updated: 2025/09/26 21:02:15 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	char	*savepoint;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined = malloc((ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	savepoint = joined;
	while (*s1)
	{
		*joined = *s1;
		joined++;
		s1++;
	}
	while (*s2)
	{
		*joined = *s2;
		joined++;
		s2++;
	}
	*joined = '\0';
	return (savepoint);
}
