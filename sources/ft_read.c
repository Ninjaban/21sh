/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:17 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/16 16:54:57 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"
#include "terms.h"

static void	ft_read_print(char **str, int c, size_t *pos)
{
	char	*tmp;
	char	*n;

	if (c != KEY_RET && c != KEY_TAB)
	{
		n = ft_strnew(2);
		n[0] = (char)c;
		tmp = ft_strjoin(*str, n);
		free(*str);
		free(n);
		*str = tmp;
	}
	if (c != KEY_TAB)
	{
		ft_putchar(c);
		*pos = *pos + 1;
	}
}

static void	ft_read_delete(char **str, size_t *pos)
{
	char	**t;
	int		len;

	if (*pos > 0 && (*str)[*pos - 1])
	{
		(*str)[*pos - 1] = '\a';
		if ((t = ft_strsplit(*str, "\a")) == NULL)
			return ;
		free(*str);
		*str = (t[0] && t[1]) ? ft_strjoin(t[0], t[1]) : NULL;
		*str = (!(*str)) ? ft_strdup(t[0]) : *str;
		*str = (!(*str)) ? ft_strnew(1) : *str;
		ft_free_tab(t);
		ft_putstr(*str + (*pos - 1));
		ft_putstr("  ");
		len = (int)ft_strlen(*str + *pos) + 3;
		while (len-- >= 0)
			ft_putchar('\b');
		*pos = *pos - 1;
	}
}

static void	ft_read_suppr(char **str, size_t *pos)
{
	char	**t;
	int		n;

	if ((*str)[*pos])
	{
		(*str)[*pos] = '\a';
		if ((t = ft_strsplit(*str, "\a")) == NULL)
			return ;
		free(*str);
		*str = (t[0] && t[1]) ? ft_strjoin(t[0], t[1]) : NULL;
		*str = (!(*str)) ? ft_strdup(t[0]) : *str;
		*str = (!(*str)) ? ft_strnew(1) : *str;
		ft_free_tab(t);
		ft_putstr(*str + *pos);
		ft_putchar(' ');
		n = (int)ft_strlen(*str + *pos);
		while (n-- >= 0)
			ft_putchar('\b');
		if (*pos > ft_strlen(*str) && *pos > 0)
			*pos = *pos - 1;
	}
}

static void	ft_read_move(char **str, int c, size_t *pos)
{
	if (c == KEY_LEF && *pos > 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	if (c == KEY_RIG && *pos < ft_strlen(*str))
		ft_putchar((*str)[(*pos)++]);
}

int			ft_read(char **str)
{
	size_t	n;
	char	exit;
	int		c;

	n = 0;
	exit = FALSE;
	*str = ft_strnew(1);
	while (exit == FALSE)
	{
		c = 0;
		read(0, &c, sizeof (int));
		if (ft_isprint(c))
			ft_read_print(&(*str), c, &n);
		if (c == KEY_RET)
			exit = TRUE;
		if (c == KEY_BAC)
			ft_read_delete(&(*str), &n);
		if (c == KEY_DEL)
			ft_read_suppr(&(*str), &n);
		if (c == KEY_UPS || c == KEY_DOW || c == KEY_LEF || c == KEY_RIG)
			ft_read_move(&(*str), c, &n);
	}
	ft_putchar('\n');
	return (TRUE);
}
