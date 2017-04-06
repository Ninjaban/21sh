/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 10:11:21 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/17 11:29:32 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(char *src)
{
	char	*str;
	size_t	n;

	n = 0;
	if (!src)
		return (NULL);
	if ((str = malloc(ft_strlen(src) + 1)) == NULL)
		return (NULL);
	while (src[n])
	{
		str[n] = src[n];
		n = n + 1;
	}
	str[n] = '\0';
	return (str);
}
