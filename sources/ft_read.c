/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 09:33:43 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 13:13:59 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "terms.h"

size_t		g_position;
size_t		g_nb;
char		**g_line;
char		**g_env;
char		**g_shvar;

void		ft_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_print(*g_line, g_position, (int)(ft_strlen(*g_line) - g_position));
	ft_putendl_fd("^C", 0);
	ft_affprompt(g_nb, g_env, g_shvar);
	if (g_line)
	{
		free(*g_line);
		*g_line = ft_strnew(1);
		g_position = 0;
	}
}

static void	ft_read_history_do(char **str, t_sys **sys, size_t *i, size_t *pos)
{
	t_lst	*tmp;

	if (*i >= (size_t)ft_list_size((*sys)->history))
		return ;
	*i = *i + 1;
	ft_print("", *pos, 0);
	tmp = ft_list_at((*sys)->history, (unsigned int)(*i));
	free(*str);
	if (tmp)
		*str = ft_strdup(((t_hist *)(tmp->data))->line);
	else
		*str = ft_strnew(1);
	*pos = ft_strlen(*str);
	ft_print(*str, 0, (int)*pos);
}

static void	ft_read_history_up(char **str, t_sys **sys, size_t *i, size_t *pos)
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
	ft_print("", *pos, 0);
	if ((tmp = ft_list_at((*sys)->history, (unsigned int)(*i - 1))))
	{
		*i = *i - 1;
		free(*str);
		*str = ft_strdup(((t_hist *)(tmp->data))->line);
	}
	*pos = (tmp && *str) ? ft_strlen(*str) : 0;
	ft_print(*str, 0, (int)*pos);
}

static void	ft_read_glob_init(size_t n, t_sys **sys)
{
	g_nb = n;
	g_env = (*sys)->env;
	g_shvar = (*sys)->shvar;
	g_position = 0;
}

int			ft_read(char **str, t_sys **sys, size_t n, char exit)
{
	size_t	i;
	int		c;

	ft_read_glob_init(n, sys);
	i = (size_t)ft_list_size((*sys)->history);
	*str = ft_strnew(1);
	g_line = &(*str);
	while (exit == FALSE)
	{
		c = 0;
		read(0, &c, sizeof(int));
		ft_removecompl(&(*str));
		exit = ft_read_check(c, &(*str), &(*sys), &g_position);
		if (c == (*sys)->keymap[KEY_EOF] && !ft_strlen(*str))
			return (FALSE);
		if (c == (*sys)->keymap[KEY_UPS])
			ft_read_history_up(&(*str), &(*sys), &i, &g_position);
		if (c == (*sys)->keymap[KEY_DOW])
			ft_read_history_do(&(*str), &(*sys), &i, &g_position);
	}
	ft_print(*str, g_position, (int)(ft_strlen(*str) - g_position));
	ft_putchar_fd('\n', 0);
	return (TRUE);
}
