/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:08:44 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/04 11:39:05 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s)
	{
		if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			return (NULL);
		i = 0;
		while (i < len)
		{
			*(str + i) = *(s + start + i);
			i++;
		}
		*(str + i) = '\0';
		return (str);
	}
	return (NULL);
}
