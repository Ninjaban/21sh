/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:22:57 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/22 13:39:26 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 && s2)
	{
		if ((str = (char *)malloc(sizeof(char)
									* (ft_strlen(s1) + ft_strlen(s2) + 1)))
			== NULL)
			return (NULL);
		ft_strcpy(str, s1);
		str = ft_strcat(str, s2);
		return (str);
	}
	return (NULL);
}
