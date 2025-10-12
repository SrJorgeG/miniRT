/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:50:42 by dcid-san          #+#    #+#             */
/*   Updated: 2025/05/20 17:52:55 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char **arr)
{
	char	**tmp;

	if (arr != NULL)
	{
		tmp = arr;
		while (*tmp != NULL)
		{
			free(*tmp);
			tmp++;
		}
		free(arr);
	}
}
