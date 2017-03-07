/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:08:09 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:52:45 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	while (*(ptr))
		ptr++;
	while (ptr >= s)
	{
		if (*(ptr) == (char)c)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
