/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:56:08 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/05 11:02:34 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_byte	*str1;
	const t_byte	*str2;
	size_t			i;

	i = 0;
	str1 = s1;
	str2 = s2;
	while (i < n)
	{
		if (*(str1 + i) != *(str2 + i))
			return ((int)(*(str1 + i) - *(str2 + i)));
		i++;
	}
	return (0);
}
