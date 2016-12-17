/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:17 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/17 10:50:40 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"
#include "terms.h"

static char	*ft_strjoin_init(char *str, char *n, size_t pos)
{
	char	*end;
	char	*tmp;
	char	*new;

	end = ft_strdup(str + pos);
	str[pos] = '\0';
	tmp = ft_strjoin(str, n);
	new = ft_strjoin(tmp, end);
	free(end);
	free(tmp);
	return (new);
}

static void	ft_read_print(char **str, int c, size_t *pos)
{
	char	*tmp;
	char	*n;
	int		len;

	if (c != KEY_RET && c != KEY_TAB)
	{
		n = ft_strnew(2);
		n[0] = (char)c;
		tmp = ft_strjoin_init(*str, n, *pos);
		free(*str);
		free(n);
		*str = tmp;
	}
	if (c != KEY_TAB)
	{
		ft_putstr(*str + *pos);
		len = (int)ft_strlen(*str + *pos) - 2;
		while (len-- >= 0)
			ft_putchar('\b');
		*pos = *pos + 1;
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

static void	ft_read_delete(char **str, size_t *pos)
{
	if (*pos > 0 && (*str)[*pos - 1])
	{
		*pos = *pos - 1;
		ft_putstr("\b");
		ft_read_suppr(&(*str), &(*pos));
	}
}

static void	ft_read_keyole(char **str, size_t *pos)
{
	while (*pos > 0 && ft_isalnum((*str)[*pos]) == 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	while (*pos > 0 && ft_isalnum((*str)[*pos]) == 1)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
}

static void	ft_read_keyori(char **str, size_t *pos)
{
	while (*pos < ft_strlen(*str) && ft_isalnum((*str)[*pos]) == 0)
		ft_putchar((*str)[(*pos)++]);
	while (*pos < ft_strlen(*str) && ft_isalnum((*str)[*pos]) == 1)
		ft_putchar((*str)[(*pos)++]);
}

static void	ft_read_move(char **str, int c, size_t *pos)
{
	if (c == KEY_LEF && *pos > 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	while (c == KEY_HOM && *pos > 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	if (c == KEY_RIG && *pos < ft_strlen(*str))
		ft_putchar((*str)[(*pos)++]);
	while (c == KEY_ENS && *pos < ft_strlen(*str))
		ft_putchar((*str)[(*pos)++]);
	if (c == KEY_OLE)
		ft_read_keyole(&(*str), &(*pos));
	if (c == KEY_ORI)
		ft_read_keyori(&(*str), &(*pos));
}

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

static void	ft_read_history_down(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i >= (size_t)ft_list_size((*sys)->history) - 1)
		return ;
	*i = *i + 1;
	ft_read_move(&(*str), KEY_HOM, &(*pos));
	ft_read_history_clear(*str);
	tmp = ft_list_at((*sys)->history, *i);
	free(*str);
	if (tmp)
		*str = ft_strdup(tmp->data);
	ft_putstr(*str);
	*pos = ft_strlen(*str);
}

static void	ft_read_history_up(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i == 0)
		return ;
	if (*i == HISTORY_SIZE + 1)
	{
		ft_history_maj(&(*sys)->history, ft_strdup(*str), (*sys)->env);
		*i = (size_t)ft_list_size((*sys)->history) - 1;
	}
	*i = *i - 1;
	ft_read_move(&(*str), KEY_HOM, &(*pos));
	ft_read_history_clear(*str);
	tmp = ft_list_at((*sys)->history, *i);
	free(*str);
	if (tmp)
		*str = ft_strdup(tmp->data);
	ft_putstr(*str);
	*pos = ft_strlen(*str);
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
		read(0, &c, sizeof (int));
		if (ft_isprint(c))
			ft_read_print(&(*str), c, &n);
		if (c == KEY_RET)
			exit = TRUE;
		if (c == KEY_BAC)
			ft_read_delete(&(*str), &n);
		if (c == KEY_DEL)
			ft_read_suppr(&(*str), &n);
		if (c == KEY_HOM || c == KEY_ENS || c == KEY_LEF || c == KEY_RIG ||
			c == KEY_OLE || c == KEY_ORI)
			ft_read_move(&(*str), c, &n);
		if (c == KEY_UPS)
			ft_read_history_up(&(*str), &(*sys), &i, &n);
		if (c == KEY_DOW)
			ft_read_history_down(&(*str), &(*sys), &i, &n);
	}
	ft_putchar('\n');
	return (TRUE);
}
