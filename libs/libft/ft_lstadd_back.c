/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:31:30 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 12:27:03 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*wrap;

	if (lst != NULL && new != NULL )
	{
		if (*lst == NULL)
		{
			*lst = new;
			return ;
		}
		wrap = *lst;
		while (wrap -> next != NULL)
		{
			wrap = wrap -> next;
		}
		wrap -> next = new;
	}
}
