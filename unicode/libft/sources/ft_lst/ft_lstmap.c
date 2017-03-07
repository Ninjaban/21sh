/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:08:34 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/13 13:20:11 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*map;
	t_list	*map_new;
	t_list	*tmp;

	map = NULL;
	while (lst)
	{
		if ((tmp = f(lst)) != NULL)
		{
			if ((map_new = ft_lstnew(tmp->content,
										tmp->content_size)) == NULL)
			{
				ft_lstdel(&map, &ft_del);
				return (NULL);
			}
			if (map)
				ft_lstadd_end(&map, map_new);
			else
				map = map_new;
			ft_lstdelone(&tmp, &ft_del);
		}
		lst = lst->next;
	}
	return (map);
}
