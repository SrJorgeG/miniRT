/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:59:29 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/10 19:20:33 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(GET_NEXT_LINE_H)
# define GET_NEXT_LINE_H
# if !defined(BUFFER_SIZE)
#  define BUFFER_SIZE 100
# endif
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char			*get_next_line(int fd);
void			*ft_realloc(void *src, unsigned long oldsize,
					unsigned long newsize);
unsigned long	ft_find_chr(char *str, char c, unsigned long size);
//char			*ft_strncpy(char *dst, const char *src, size_t dsize);
char			*ft_buffzero(char *buff);

#endif
