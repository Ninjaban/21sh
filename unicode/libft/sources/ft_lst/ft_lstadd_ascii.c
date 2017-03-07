/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 12:35:38 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/04 12:44:08 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_ascii(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (!(new->content))
		return ;
	while (tmp && (char *)(tmp->content)
			&& ft_strcmp((char *)(tmp->content), (char *)(new->content)) < 0)
		tmp = tmp->next;
	new->next = tmp;
	if (tmp == *alst)
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp && tmp->next && tmp->next != new->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
