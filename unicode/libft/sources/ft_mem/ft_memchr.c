/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:49:08 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/05 11:03:56 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const t_byte	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (i < n)
	{
		if (*(ptr + i) == (t_byte)c)
			return ((void *)(ptr + sizeof(t_byte) * i));
		i++;
	}
	return (NULL);
}
