/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:08:01 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/04 18:53:15 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_nbsize(int n)
{
	unsigned int	size;
	unsigned int	nbr;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
		size++;
	nbr = ABS(n);
	while (nbr > 0)
	{
		size++;
		nbr = nbr / 10;
	}
	return (size);
}

static char			*get_str(char *str, unsigned int size, int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = ABS(n);
	while (nbr)
	{
		str[size - (i + 1)] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i++;
	}
	return (str);
}

char				*ft_itoa(int n)
{
	unsigned int	size;
	char			*str;

	size = get_nbsize(n);
	if ((str = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	str = get_str(str, size, n);
	str[size] = '\0';
	return (str);
}
