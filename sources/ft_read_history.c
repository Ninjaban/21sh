/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 11:13:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/18 11:21:47 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_read_history_do(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i >= (size_t)ft_list_size((*sys)->history))
		return ;
	*i = *i + 1;
	ft_print("", *pos, 0, FALSE);
	tmp = ft_list_at((*sys)->history, (unsigned int)(*i));
	free(*str);
	if (tmp)
		*str = ft_strdup(((t_hist *)(tmp->data))->line);
	else
		*str = ft_strnew(1);
	*pos = ft_strlen(*str);
	ft_print(*str, 0, (int)*pos, FALSE);
	if (!ft_strlen(*str))
		ft_putstr(" \b");
}

void		ft_read_history_up(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;
	char	ret;

	if (*i == 0)
		return ;
	if (*i == (size_t)ft_list_size((*sys)->history))
	{
		ret = (char)ft_history_maj(&(*sys)->history, *str,
									(*sys)->env, (*sys)->shvar);
		*i = (size_t)ft_list_size((*sys)->history) - ((ret) ? 1 : 0);
	}
	ft_print("", *pos, 0, FALSE);
	if ((tmp = ft_list_at((*sys)->history, (unsigned int)(*i - 1))))
	{
		*i = *i - 1;
		free(*str);
		*str = ft_strdup(((t_hist *)(tmp->data))->line);
	}
	*pos = (tmp && *str) ? ft_strlen(*str) : 0;
	ft_print(*str, 0, (int)*pos, FALSE);
}
