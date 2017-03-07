/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:59:41 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/09 10:54:53 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n && *(s1 + i) && *(s2 + i) && (*(s1 + i) == *(s2 + i)))
		i++;
	if (i == n)
		return ((unsigned char)*(s1 + i - 1) - (unsigned char)*(s2 + i - 1));
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}
