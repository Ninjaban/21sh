/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:43:12 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/04 11:38:15 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*str;
	unsigned int	i;

	if (s)
	{
		if ((str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
			return (NULL);
		i = 0;
		while (*(s + i))
		{
			*(str + i) = f(*(s + i));
			i++;
		}
		*(str + i) = '\0';
		return (str);
	}
	return (NULL);
}
