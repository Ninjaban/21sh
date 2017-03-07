/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:21:33 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:50:25 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;

	if (!dest || !src)
		return (0);
	dlen = ft_strlen(dest);
	if (size <= dlen)
		return (ft_strlen(src) + size);
	i = 0;
	while (src[i] && (dlen + i) < (size - 1))
	{
		dest[dlen + i] = src[i];
		i++;
	}
	if ((dlen + i) < size)
		dest[dlen + i] = '\0';
	return (dlen + ft_strlen(src));
}
