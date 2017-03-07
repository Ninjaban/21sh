/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 13:00:23 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/13 13:02:11 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char const *s1, char const *s2, char c)
{
	char	*str;
	size_t	n;

	if (s1 && s2)
	{
		if ((str = (char *)malloc(sizeof(char)
									* (ft_strlen(s1) + ft_strlen(s2) + 2)))
			== NULL)
			return (NULL);
		ft_strcpy(str, s1);
		n = ft_strlen(s1);
		str[n] = c;
		str[n + 1] = '\0';
		str = ft_strcat(str, s2);
		return (str);
	}
	return (NULL);
}
