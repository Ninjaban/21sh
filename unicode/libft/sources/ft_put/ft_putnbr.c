/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:28:59 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/09 11:38:09 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	nbr;
	char			tab[10];
	int				i;

	if (n < 0)
		write(1, "-", 1);
	if (n == 0)
	{
		write(1, "0", 1);
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
		write(1, &(tab[i]), 1);
		i--;
	}
}
