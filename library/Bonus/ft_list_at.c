/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 10:42:07 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/09 11:32:31 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_list_at(t_lst *begin_list, unsigned int nbr)
{
	t_lst			*elem;
	unsigned int	n;

	n = 0;
	elem = begin_list;
	while (n < nbr && elem->next != NULL)
	{
		elem = elem->next;
		n = n + 1;
	}
	if (n < nbr)
		return (NULL);
	return (elem);
}
