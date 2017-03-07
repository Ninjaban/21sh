/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:13:55 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:55:11 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	chklittle(char const *b, char const *l)
{
	unsigned int	i;

	i = 0;
	while (*(b + i) && *(l + i) && (*(b + i) == *(l + i)))
		i++;
	if (*(l + i) == 0)
		return (0);
	return (1);
}

char		*ft_strstr(const char *big, const char *little)
{
	size_t	size;
	char	*b;

	if (!big || !little)
		return (NULL);
	b = (char *)big;
	size = ft_strlen(little);
	if (size == 0)
		return (b);
	else if (ft_strlen(big) < size)
		return (NULL);
	while (*(b + size - 1))
	{
		if (chklittle((const char *)b, little) == 0)
			return (b);
		b++;
	}
	return (NULL);
}
