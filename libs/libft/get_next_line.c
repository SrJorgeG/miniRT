/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:59:25 by dcid-san          #+#    #+#             */
/*   Updated: 2025/10/10 19:20:39 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	set_sizes(unsigned long *read_pos, unsigned long *old_size,
		unsigned long *line_len)
{
	*read_pos += *line_len;
	*old_size += *line_len;
}

ssize_t	read_buffer(int fd, unsigned long *read_pos,
				ssize_t *read_size, char *buffer)
{
	if (buffer != NULL)
		ft_buffzero(buffer);
	*read_size = read(fd, buffer, BUFFER_SIZE);
	*read_pos = 0;
	return (*read_size);
}

char	*get_next_line2(int fd, unsigned long *read_pos,
		ssize_t *read_size, char *buffer)
{
	char					*line;
	unsigned long			line_len;
	unsigned long			old_size;

	old_size = 0;
	line = NULL;
	while (1)
	{
		if (*read_pos >= (unsigned long)*read_size)
		{
			read_buffer(fd, read_pos, read_size, buffer);
			if (*read_size == -1)
				return (ft_buffzero(buffer), free(line),
					read_pos = 0, read_size = 0, NULL);
			if (*read_size == 0)
				return (ft_buffzero(buffer), read_pos = 0, line);
		}
		line_len = ft_find_chr(buffer + *read_pos, '\n', *read_size) + 1;
		line = ft_realloc(line, old_size, old_size + line_len + 1);
		ft_strncpy(line + old_size, buffer + *read_pos, line_len + 1);
		set_sizes(read_pos, &old_size, &line_len);
		if (line[old_size - 1] == '\n')
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static unsigned long	read_pos = 0;
	static ssize_t			read_size = 0;
	static char				buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_buffzero(buffer), read_pos = 0, read_size = 0, NULL);
	if (read_size == -1)
		read_size = 0;
	return (get_next_line2(fd, &read_pos, &read_size, buffer));
}
