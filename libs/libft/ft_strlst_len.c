/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlst_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:33:37 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/11 00:38:12 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

size_t	ft_strlst_len(char **strlst)
{
	size_t	count;

	if (!strlst)
		return (0);
	count = 0;
	while (*strlst)
	{
		count++;
		strlst++;
	}
	return (count);
}