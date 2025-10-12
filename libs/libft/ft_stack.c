/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:59:08 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 13:03:14 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Crea un stack vacío */
t_stack	*ft_stack_new(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->first = NULL;
	stack->last = NULL;
	stack->size = 0;
	return (stack);
}

/* Añade un nodo al final */
void	ft_stack_add_back(t_stack *lst, t_list *node)
{
	if (!lst || !node)
		return ;
	if (!lst->first)
		lst->first = node;
	else
		lst->last->next = node;
	lst->last = node;
	node->next = NULL;
	lst->size++;
}

/* Añade un nodo al principio */
void	ft_stack_add_front(t_stack *lst, t_list *node)
{
	if (!lst || !node)
		return ;
	node->next = lst->first;
	lst->first = node;
	if (!lst->last)
		lst->last = node;
	lst->size++;
}

/* Devuelve el primer nodo sin quitarlo */
t_list	*ft_stack_first(t_stack *lst)
{
	if (!lst)
		return (NULL);
	return (lst->first);
}

/* Devuelve el último nodo sin quitarlo */
t_list	*ft_stack_last(t_stack *lst)
{
	if (!lst)
		return (NULL);
	return (lst->last);
}
