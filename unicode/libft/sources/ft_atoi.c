/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:17:45 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/09 11:40:42 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_whitesp(const char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static unsigned int	get_nbr(char *s)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	nbr = 0;
	while (*s == '0')
		s++;
	while (*(s + i) && ft_isdigit(*(s + i)))
	{
		nbr = (nbr * 10) + (*(s + i) - '0');
		i++;
	}
	return (nbr);
}

int					ft_atoi(const char *str)
{
	char			*s;
	unsigned int	nbr;
	int				sign;

	sign = 1;
	s = (char *)str;
	while (is_whitesp(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		sign = (*s == '-' ? -1 : 1);
		s++;
	}
	nbr = get_nbr(s);
	return (sign * nbr);
}
