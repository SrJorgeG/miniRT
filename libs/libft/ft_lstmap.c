/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:33:19 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 12:27:03 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_list;
	t_list	*nodenew;

	if (!lst || !f)
		return (NULL);
	map_list = ft_lstnew(lst->content);
	if (!map_list)
		return (NULL);
	nodenew = map_list;
	lst = lst -> next;
	while (!lst)
	{
		nodenew -> next = f(lst -> content);
		if (!nodenew -> next)
		{
			ft_lstclear(&map_list, del);
			return (NULL);
		}
		nodenew = nodenew -> next;
		lst = lst -> next;
	}
	return (map_list);
}

/* int main(void)
{
	ft_lstmap(NULL, NULL,NULL);
	return (0);
} */