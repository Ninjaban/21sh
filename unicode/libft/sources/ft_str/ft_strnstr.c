/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:35:29 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:52:25 by mrajaona         ###   ########.fr       */
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

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	size;
	size_t	i;

	if (!big || !little)
		return (NULL);
	size = ft_strlen(little);
	if (size == 0)
		return ((char *)big);
	else if (ft_strlen(big) < size)
		return (NULL);
	i = 0;
	while ((i + size) <= len && *(big + i + size - 1))
	{
		if (chklittle(big + i, little) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
