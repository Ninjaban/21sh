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
		ft_putchar_fd('\b', 0);
	n = (int)len_s;
	while (n-- > 0)
		ft_putchar_fd(' ', 0);
	while (len_s-- > 0)
		ft_putchar_fd('\b', 0);
	len_s = (ft_checkcompl(str) == 1) ? ft_strlen(str) - 13 : ft_strlen(str);
	n = (int)len_s - 1;
	ft_putstr_fd(str, 0);
	while (n-- >= (int)pos + inc)
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

void		ft_read_print(char **str, int c, size_t *pos, char **env)
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
	ft_completion(&(*str), (c == KEY_TAB) ? (*pos) : (*pos) + 1,
				env, (c == KEY_TAB) ? 1 : 0);
	ft_print(*str, (*pos), (c == KEY_TAB) ? 0 : 1);
	if (c != KEY_TAB)
		*pos = *pos + 1;
	else
		ft_read_keyori(&(*str), &(*pos));
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
		ft_putchar('\b');
		ft_read_suppr(&(*str), &(*pos));
	}
}
