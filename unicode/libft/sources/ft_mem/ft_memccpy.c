/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:02:39 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/05 11:03:37 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_byte			*d;
	const t_byte	*s;
	size_t			i;

	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		*(d + i) = *(s + i);
		if (*(s + i) == (t_byte)c)
			return (d + sizeof(t_byte) * (i + 1));
		i++;
	}
	return (NULL);
}
