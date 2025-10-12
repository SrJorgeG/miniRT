/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_strlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:52:40 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/12 12:27:03 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* 
* Returns a char* list with the content of each node of a t_list
*/
char	**ft_lst_to_strlist(t_list *first)
{
	char	**argv;
	t_list	*wrapper;
	size_t	lstsize;

	lstsize = ft_lstsize(first);
	argv = malloc(sizeof(char *) * (lstsize + 1));
	argv[lstsize] = NULL;
	wrapper = first;
	lstsize = 0;
	while (wrapper)
	{
		argv[lstsize] = wrapper->content;
		wrapper = wrapper->next;
		lstsize++;
	}
	return (argv);
}
