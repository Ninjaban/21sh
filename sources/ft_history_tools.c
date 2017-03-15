/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 14:23:11 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/15 11:53:04 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_lst	*ft_create_hist_elem(char *line)
{
	t_lst		*new_elem;
	t_hist		*data;
	static int	id = 1;

	if ((new_elem = (t_lst *)malloc(sizeof(t_lst))) == NULL)
		return (NULL);
	new_elem->next = NULL;
	if ((data = (t_hist *)malloc(sizeof(t_hist))) == NULL)
	{
		free(new_elem);
		return (NULL);
	}
	data->line = line;
	data->id = id;
	new_elem->data = (void *)data;
	id++;
	return (new_elem);
}

void	ft_list_push_back_id(t_lst **begin_list, char *line)
{
	t_lst		*new_elem;
	t_lst		*elem;

	if (!begin_list || !line)
		return ;
	if ((new_elem = ft_create_hist_elem(line)) == NULL)
		return ;
	elem = *begin_list;
	if (elem == NULL)
		*begin_list = new_elem;
	else
	{
		while (elem->next != NULL)
			elem = elem->next;
		elem->next = new_elem;
	}
}
