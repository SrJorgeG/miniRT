/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:32:01 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 12:27:03 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*wrapper;
	t_list	*cpy;

	if (lst != NULL && *lst != NULL && del != NULL)
	{
		wrapper = *lst;
		while (wrapper -> next != NULL)
		{
			cpy = wrapper-> next;
			ft_lstdelone(wrapper, del);
			wrapper = cpy;
		}
		ft_lstdelone(wrapper, del);
		*lst = NULL;
	}
}
