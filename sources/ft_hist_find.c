/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hist_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 12:37:27 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/21 11:11:47 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

/*
** search s2 in s1
*/

int			ft_hist_match(char *s1, char *s2)
{
	if (!(*s1) && !(*s2))
		return (1);
	else if (*s1 == *s2)
	{
		if (*(s1) == '?')
			return (ft_hist_match(s1 + 1, s2) || ft_hist_match(s1, s2 + 1));
		else
			return (ft_hist_match(s1 + 1, s2 + 1));
	}
	else if (*s2 == '?')
	{
		if (!*s1)
			return (ft_hist_match(s1, s2 + 1));
		else
			return (ft_hist_match(s1 + 1, s2) || ft_hist_match(s1, s2 + 1));
	}
	return (0);
}

char		*ft_hist_find(t_lst *history, char *str)
{
	t_lst	*tmp;
	char	*res;

	if (!str)
		return (NULL);
	if (*str == '\0' || ft_strcmp(str, "?") == 0 || ft_strcmp(str, "??") == 0)
	{
		free(str);
		return (ft_error_void(ERROR_HIST));
	}
	tmp = history;
	res = NULL;
	while (tmp)
	{
		if (ft_hist_match(((t_hist *)(tmp->data))->line, str) == 1)
			res = ((t_hist *)(tmp->data))->line;
		tmp = tmp->next;
	}
	free(str);
	if (!res)
		return (ft_error_void(ERROR_HIST));
	return (res);
}

char		*ft_hist_id(t_lst *history, char *str)
{
	t_lst	*tmp;
	int		id;

	id = ft_atoi(str);
	tmp = history;
	if (id > 0 && id < ((t_hist *)(tmp->data))->id)
		return (ft_error_void(ERROR_HIST));
	if (id < 0)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		id = ((t_hist *)(tmp->data))->id + 1 + id;
		tmp = history;
	}
	if (id < ((t_hist *)(tmp->data))->id)
		return (ft_error_void(ERROR_HIST));
	while (tmp)
	{
		if (id == ((t_hist *)(tmp->data))->id)
			return (((t_hist *)(tmp->data))->line);
		tmp = tmp->next;
	}
	return (ft_error_void(ERROR_HIST));
}

char		*ft_hist_last(t_lst *history)
{
	t_lst	*tmp;

	tmp = history;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		ft_log(TYPE_ERROR, ERROR_HIST);
	return (tmp ? ((t_hist *)(tmp->data))->line : NULL);
}
