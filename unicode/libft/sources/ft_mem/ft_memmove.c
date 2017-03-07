/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:25:08 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/05 11:58:35 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	t_byte			*d;
	const t_byte	*s;
	t_byte			*tmp;
	size_t			n;

	d = dst;
	s = src;
	if ((tmp = (t_byte *)malloc(sizeof(t_byte) * len)) == NULL)
		return (dst);
	n = 0;
	while (n < len)
	{
		*(tmp + n) = *(s + n);
		n++;
	}
	n = 0;
	while (n < len)
	{
		*(d + n) = *(tmp + n);
		n++;
	}
	free(tmp);
	return (dst);
}
