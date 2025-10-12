/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:14:18 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/25 19:49:03 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *str)
{
	char	*wrap;

	if (NULL == str)
		return (NULL);
	wrap = str;
	while (*wrap)
	{
		*wrap = ft_tolower(*wrap);
		wrap++;
	}
	return (str);
}
