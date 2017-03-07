/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:22:34 by mrajaona          #+#    #+#             */
/*   Updated: 2017/01/13 15:57:56 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
		new->content = NULL;
	else if ((new->content = malloc(content_size)) == NULL)
	{
		free(new);
		return (NULL);
	}
	else
		new->content = ft_memcpy(new->content, content, content_size);
	new->content_size = (content == NULL ? 0 : content_size);
	new->next = NULL;
	return (new);
}
