/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:33:19 by dcid-san          #+#    #+#             */
/*   Updated: 2025/05/25 20:49:08 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstfind_cmp(void *lst, void *target, int (*cmp)(void *, void *))
{
	while (lst)
	{
		if (cmp(lst, target))
			return (lst);
		lst = ((t_list *)lst)->next;
	}
	return (NULL);
}
