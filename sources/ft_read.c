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

void		ft_print(char *str, size_t pos, char inc)
{
	static size_t	len_s = 0;
	int				n;

	n = (int)pos;
	while (n-- > 0)
		ft_putchar('\b');
	n = (int)len_s;
	while (n-- > 0)
		ft_putchar(' ');
	while (len_s-- > 0)
		ft_putchar('\b');
	len_s = (ft_checkcompl(str) == 1) ? ft_strlen(str) - 12 : ft_strlen(str);
	n = (int)len_s - 1;
	ft_putstr(str);
	while (n-- >= (int)pos + inc)
		ft_putchar('\b');
}

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

static void	ft_read_print(char **str, int c, size_t *pos, char **env)
{
	char	*tmp;
	char	*n;

	if (c != KEY_RET && c != KEY_TAB)
	{
		n = ft_strnew(2);
		n[0] = (char)c;
		tmp = ft_strjoin_init(*str, n, *pos);
		free(*str);
		free(n);
		*str = tmp;
	}
	ft_completion(&(*str), (c == KEY_TAB) ? (*pos) : (*pos) + 1, env, (c == KEY_TAB) ? 1 : 0);
	ft_print(*str, (*pos), (c == KEY_TAB) ? 0 : 1);
	if (c != KEY_TAB)
		*pos = *pos + 1;
}

static void	ft_read_suppr(char **str, size_t *pos)
{
	char	**t;

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
		ft_print(*str, (*pos), 0);
		if (*pos > ft_strlen(*str) && *pos > 0)
			*pos = *pos - 1;
	}
}

static void	ft_read_delete(char **str, size_t *pos)
{
	if (*pos > 0 && (*str)[*pos - 1])
	{
		*pos = *pos - 1;
		ft_putchar('\b');
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
	ft_print(*str, *pos, 0);
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

static void	ft_read_history_do(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i >= (size_t)ft_list_size((*sys)->history) - 1)
		return ;
	*i = *i + 1;
	ft_read_move(&(*str), KEY_HOM, &(*pos));
	ft_read_history_clear(*str);
	free(*str);
	tmp = ft_list_at((*sys)->history, *i);
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
		*i = (size_t)ft_list_size((*sys)->history);
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
		read(0, &c, sizeof(int));
		ft_removecompl(&(*str));
		if (ft_isprint(c) || c == KEY_TAB)
			ft_read_print(&(*str), c, &n, (*sys)->env);
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
			ft_read_history_do(&(*str), &(*sys), &i, &n);
	}
	ft_print(*str, n, 0);
	ft_putchar('\n');
	return (TRUE);
}
