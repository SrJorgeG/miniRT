/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:04:00 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/27 15:17:18 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;
	size_t	size;

	size = ft_strlen(s);
	res = malloc((size + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[size] = 0;
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}

/* char	func(unsigned int x, char y)
{
	return (x + y);
}

int main (void)
{
	ft_strmapi("abcd0 ", func);
}
 */