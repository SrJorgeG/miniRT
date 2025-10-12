/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 13:02:57 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 13:03:20 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Extrae y devuelve el primer nodo */
t_list	*ft_stack_pop_front(t_stack *lst)
{
	t_list	*node;

	if (!lst || !lst->first)
		return (NULL);
	node = lst->first;
	lst->first = node->next;
	if (!lst->first)
		lst->last = NULL;
	node->next = NULL;
	lst->size--;
	return (node);
}

/* Extrae y devuelve el último nodo */
t_list	*ft_stack_pop_back(t_stack *lst)
{
	t_list	*prev;
	t_list	*node;

	if (!lst || !lst->first)
		return (NULL);
	if (lst->first == lst->last)
	{
		node = lst->first;
		lst->first = NULL;
		lst->last = NULL;
	}
	else
	{
		prev = lst->first;
		while (prev->next != lst->last)
			prev = prev->next;
		node = lst->last;
		prev->next = NULL;
		lst->last = prev;
	}
	lst->size--;
	return (node);
}

/* Devuelve el tamaño de la pila */
size_t	ft_stack_size(t_stack *lst)
{
	if (!lst)
		return (0);
	return (lst->size);
}

/* Devuelve 1 si la pila está vacía */
int	ft_stack_is_empty(t_stack *lst)
{
	if (!lst || lst->size == 0)
		return (1);
	return (0);
}

/* Libera todos los nodos y el stack */
void	ft_stack_clear(t_stack *lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst->first)
	{
		tmp = lst->first->next;
		if (del)
			del(lst->first->content);
		free(lst->first);
		lst->first = tmp;
	}
	lst->last = NULL;
	lst->size = 0;
}
