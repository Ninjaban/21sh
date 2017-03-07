/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:18:03 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:51:03 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	tmp = s1;
	while (*tmp)
		tmp++;
	i = 0;
	while (i < n && s2[i])
	{
		tmp[i] = s2[i];
		i++;
	}
	tmp[i] = '\0';
	return (s1);
}
