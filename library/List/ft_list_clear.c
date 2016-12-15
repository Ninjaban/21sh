/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lis_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 10:35:16 by jcarra            #+#    #+#             */
/*   Updated: 2016/11/09 11:32:22 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_clear(t_lst **begin_list)
{
	t_lst	*elem;
	t_lst	*next;

	if (begin_list && *begin_list)
	{
		elem = *begin_list;
		next = elem->next;
		while (elem->next != NULL)
		{
			free(elem);
			elem = next;
			next = elem->next;
		}
		begin_list = NULL;
	}
}
