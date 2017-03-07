/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:44:26 by mrajaona          #+#    #+#             */
/*   Updated: 2016/11/09 10:00:22 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*atmp;
	t_list	*btmp;

	atmp = *alst;
	while (atmp)
	{
		btmp = atmp;
		atmp = atmp->next;
		ft_lstdelone(&btmp, del);
		free(btmp);
	}
	*alst = NULL;
}
