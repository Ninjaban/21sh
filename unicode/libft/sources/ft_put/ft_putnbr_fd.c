/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:06:55 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/09 11:39:33 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;
	char			tab[10];
	int				i;

	if (n < 0)
		write(fd, "-", 1);
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	nbr = ABS(n);
	i = 0;
	while (i < 10 && nbr > 0)
	{
		tab[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		if (nbr > 0)
			i++;
	}
	while (i >= 0)
	{
		write(fd, &(tab[i]), 1);
		i--;
	}
}
