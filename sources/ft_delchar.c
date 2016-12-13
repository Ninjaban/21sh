/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 10:53:13 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/07 12:05:11 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_delchar(char *str, size_t n)
{
	char	*new;
	size_t	i;

	i = 0;
	if ((new = ft_strnew(ft_strlen(str))) == NULL)
		return (NULL);
	while (i < n)
	{
		new[i] = str[i];
		i = i + 1;
	}
	while (++i < ft_strlen(str))
	{
		new[i - 1] = str[i];
	}
	free(str);
	return (new);
}
