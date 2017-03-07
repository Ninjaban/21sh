/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:49:35 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/04 11:38:02 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
			*(str + i) = f(i, *(s + i));
			i++;
		}
		*(str + i) = '\0';
		return (str);
	}
	return (NULL);
}
