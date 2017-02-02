/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:17 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/09 16:45:59 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "terms.h"

static void	ft_read_history_clear(char *str)
{
	size_t	n;

	n = ft_strlen(str);
	while (n-- > 0)
		ft_putchar(' ');
	n = ft_strlen(str);
	while (n-- > 0)
		ft_putchar('\b');
}

static void	ft_read_history_do(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i >= (size_t)ft_list_size((*sys)->history) - 1)
		return ;
	*i = *i + 1;
	ft_read_move(&(*str), KEY_HOM, &(*pos));
	ft_read_history_clear(*str);
	tmp = ft_list_at((*sys)->history, *i);
	if (tmp)
	{
		free(*str);
		if ((*str = ft_strdup(tmp->data)) != NULL)
			ft_putstr(*str);
		*pos = (*str) ? ft_strlen(*str) : 0;
	}
	else
		*i = *i - 1;
}

static void	ft_read_history_up(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i == 0)
		return ;
	if (*i == HISTORY_SIZE + 1)
	{
		ft_history_maj(&(*sys)->history, *str, (*sys)->env);
		*i = (size_t)ft_list_size((*sys)->history);
	}
	*i = *i - 1;
	ft_read_move(&(*str), KEY_HOM, &(*pos));
	ft_read_history_clear(*str);
	tmp = ft_list_at((*sys)->history, *i);
	if (tmp)
	{
		free(*str);
		if ((*str = ft_strdup(tmp->data)) != NULL)
			ft_putstr(*str);
		*pos = (*str) ? ft_strlen(*str) : 0;
	}
	else
		*i = *i + 1;
}

static char	ft_read_check(int c, char **str, t_sys **sys, size_t *n)
{
	if (c == KEY_RET)
		return (TRUE);
	if (ft_isprint(c) || c == KEY_TAB)
		ft_read_print(&(*str), c, &(*n), (*sys)->env);
	if (c == KEY_BAC)
		ft_read_delete(&(*str), &(*n));
	if (c == KEY_DEL)
		ft_read_suppr(&(*str), &(*n));
	if (c == KEY_HOM || c == KEY_ENS || c == KEY_LEF || c == KEY_RIG ||
		c == KEY_OLE || c == KEY_ORI)
		ft_read_move(&(*str), c, &(*n));
	return (FALSE);
}

int			ft_read(char **str, t_sys **sys)
{
	size_t	n;
	size_t	i;
	char	exit;
	int		c;

	n = 0;
	i = HISTORY_SIZE + 1;
	exit = FALSE;
	*str = ft_strnew(1);
	while (exit == FALSE)
	{
		c = 0;
		read(0, &c, sizeof(int));
		ft_removecompl(&(*str));
		exit = ft_read_check(c, &(*str), &(*sys), &n);
		if (c == KEY_UPS)
			ft_read_history_up(&(*str), &(*sys), &i, &n);
		if (c == KEY_DOW)
			ft_read_history_do(&(*str), &(*sys), &i, &n);
	}
	ft_print(*str, n, 0);
	ft_putchar('\n');
	return (TRUE);
}
