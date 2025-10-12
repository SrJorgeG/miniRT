/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:12:12 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/27 14:17:30 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long int	ncpy;
	char		wrap;

	ncpy = n;
	if (ncpy < 0)
	{
		write(fd, "-", 1);
		ncpy *= -1;
	}
	if (ncpy / 10 != 0)
		ft_putnbr_fd(ncpy / 10, fd);
	wrap = ncpy % 10 + '0';
	write(fd, &wrap, 1);
}

/* int	main(void)
{
	ft_putnbr_fd(0, 1);
	return (0);
}
 */