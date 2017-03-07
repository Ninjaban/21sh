/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 09:51:01 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/05 10:32:23 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_byte			*d;
	const t_byte	*s;

	d = dst;
	s = src;
	while (n)
	{
		*(d + n - 1) = *(s + n - 1);
		n--;
	}
	return (dst);
}
