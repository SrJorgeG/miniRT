/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:14:05 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/27 14:34:50 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*strcpy;
	int		size;
	int		i;

	size = ft_strlen(s);
	strcpy = malloc((size + 1) * sizeof (char));
	if (strcpy == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
	{
		strcpy[i] = s[i];
	}
	strcpy[i] = '\0';
	return (strcpy);
}
