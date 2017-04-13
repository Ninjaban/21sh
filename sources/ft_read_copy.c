/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 12:00:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/01 12:00:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_read_cpy(char *str, size_t n, char **buf)
{
	char		*tmp;
	int			i;

	tmp = (*buf) ? ft_strdup(*buf) : NULL;
	if (*buf)
		free(*buf);
	if ((*buf = ft_strnew((tmp) ? ft_strlen(tmp) + 2 : 2)) == NULL)
		return (free(tmp));
	i = -1;
	if (tmp)
		while (tmp[++i])
			(*buf)[i] = tmp[i];
	else
		i = 0;
	free(tmp);
	(*buf)[i] = str[n];
}

void		ft_strjoinf(char **src, char *str)
{
	char	*tmp;

	if (src && *src && str)
	{
		tmp = ft_strjoin(*src, str);
		free(*src);
		*src = tmp;
	}
}

void		ft_read_past(char **str, size_t *n, char *buf)
{
	char	*tmp;
	char	c;

	c = (*str)[*n];
	(*str)[*n] = '\0';
	tmp = ft_strdup(*str);
	ft_strjoinf(&tmp, buf);
	(*str)[*n] = c;
	ft_strjoinf(&tmp, *str + *n);
	free(*str);
	*str = tmp;
	ft_print(*str, *n, (int)ft_strlen(buf), FALSE);
	*n = *n + ft_strlen(buf);
}

void		ft_read_cpy_past(char **str, size_t *n, char type_cpy, char new_cpy)
{
	static char	*buf = NULL;

	if (type_cpy == TRUE)
	{
		if (new_cpy)
			ft_strdel(&(buf));
		ft_read_cpy(*str, *n, &buf);
	}
	else
		ft_read_past(&(*str), &(*n), buf);
}

void		ft_read_keymap_init(t_sys **sys)
{
	char	**tab;

	if ((tab = malloc(sizeof(char *) * 3)) == NULL)
		return ;
	tab[0] = ft_strdup("keymap");
	tab[1] = ft_strdup("--reset");
	tab[2] = NULL;
	ft_keymap(&((*sys)->keymap), tab, *sys);
	ft_free_tab(tab);
}
