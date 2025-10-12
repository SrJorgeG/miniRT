/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcid-san <dcid-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:09:32 by dcid-san          #+#    #+#             */
/*   Updated: 2024/09/27 14:35:07 by dcid-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_numdigits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0 || n == 0)
		digits++;
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int			digits;
	char		*str;
	long int	ncpy;

	ncpy = n;
	digits = ft_numdigits(ncpy);
	if (n < 0)
		ncpy *= -1;
	str = malloc((digits + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[digits] = 0;
	while (digits--)
	{
		str[digits] = (ncpy % 10) + 48;
		ncpy /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/* #include <stdio.h>
int main(void)
{
	char *str1 = ft_itoa(0);
	printf("%s\n", str1);
	char *str2 = ft_itoa(2147483647);
	printf("%s\n", str2);
	char *str3 = ft_itoa(-2147483648);
	printf("%s\n", str3);
	return (0);
}
 */