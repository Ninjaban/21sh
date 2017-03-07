/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 12:16:36 by mrajaona          #+#    #+#             */
/*   Updated: 2016/12/17 12:18:17 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap(t_list **prev, t_list **a, t_list **b, t_list **list)
{
	(*a)->next = (*b)->next;
	(*b)->next = (*a);
	if ((*prev) == *a)
		*list = *b;
	else if (*prev != *a)
		(*prev)->next = *b;
}
