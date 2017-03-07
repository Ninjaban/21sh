/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 10:10:52 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/05 10:24:35 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	t_byte		*ptr;
	size_t		i;

	if ((ptr = (t_byte *)malloc(sizeof(t_byte) * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
