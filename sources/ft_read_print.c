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

void		ft_print(char *str, size_t pos, int inc)
{
	static size_t	len_s = 0;
	char			*tmp;
	int				n;
	int				i;

	if ((tmp = ft_strnew(pos + (len_s * 2) + 3)) == NULL)
		return ;
	n = 0;
	while (n < (int)pos - 1)
		tmp[n++] = '\b';
	i = 0;
	while (i < (int)len_s)
		tmp[n + i++] = ' ';
	while (len_s > 0)
		tmp[n + i + len_s--] = '\b';
	tmp[n + i] = '\b';
	if (!(pos || !inc))
		tmp[ft_strlen(tmp) - 1] = '\0';
	if (!(pos == 0 && inc == 0))
		ft_putstr_fd(tmp, 0);
	else
		ft_putstr_fd(" \b", 0);
	free(tmp);
	len_s = (ft_checkcompl(str) == 1) ? ft_strlen(str) - 19 : ft_strlen(str);
	n = (int)len_s;
	ft_read_color_main(str);
	while (n-- > (int)pos + inc)
		ft_putchar_fd('\b', 0);
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
		*str = (t[0] && t[1]) ? ft_strjoin(t[0], t[1]) : NULL;
		*str = (!(*str)) ? ft_strdup(t[0]) : *str;
		*str = (!(*str)) ? ft_strnew(1) : *str;
		ft_free_tab(t);
		ft_print(*str, (*pos), 0);
		if (*pos > ft_strlen(*str) && *pos > 0)
			*pos = *pos - 1;
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
