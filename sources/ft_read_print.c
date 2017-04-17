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

void		ft_read_print(char **str, int c, size_t *pos, t_sys **sys)
{
	char	*tmp;
	char	*n;

	if (c != (*sys)->keymap[KEY_TAB])
	{
		n = ft_strnew(2);
		n[0] = (char)c;
		tmp = ft_strjoin_init(*str, n, *pos);
		free(*str);
		free(n);
		*str = tmp;
	}
}

void		ft_read_suppr(char **str, size_t *pos)
{
	char	**t;

	if ((*str)[*pos])
	{
		(*str)[*pos] = '\a';
		if ((t = ft_strsplit(*str, "\a")) == NULL)
			return ;
		free(*str);
		*str = (t[0] && t[1]) ? ft_strjoin(t[0], t[1]) : ft_strdup(t[0]);
		*str = (!(*str)) ? ft_strnew(1) : *str;
		ft_free_tab(t);
		ft_print(*str, *pos, 0, FALSE);
//		if ((*str)[*pos])
//			ft_putchar_fd('\b', 0);
	}
}

void		ft_read_delete(char **str, size_t *pos)
{
	if (*pos > 0 && (*str)[*pos - 1])
	{
		*pos = *pos - 1;
		ft_putchar_fd('\b', 0);
		ft_read_suppr(&(*str), &(*pos));
	}
}
