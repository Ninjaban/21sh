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

void		ft_read_history_clear(char *str)
{
	size_t	n;

	n = ft_strlen(str);
	while (n-- > 0)
		ft_putchar_fd(' ', 0);
	n = ft_strlen(str);
	while (n-- > 0)
		ft_putchar_fd('\b', 0);
}

void		ft_read_keyole(char **str, size_t *pos)
{
	while (*pos > 0 && (*str)[*pos] == ' ')
	{
		ft_putchar_fd('\b', 0);
		*pos = *pos - 1;
	}
	while (*pos > 0 && (*str)[*pos] != ' ')
	{
		ft_putchar_fd('\b', 0);
		*pos = *pos - 1;
	}
}

void		ft_read_keyori(char **str, size_t *pos)
{
	while (*pos < ft_strlen(*str) && (*str)[*pos] == ' ' && (*str)[*pos])
		ft_putchar_fd((*str)[(*pos)++], 0);
	while (*pos < ft_strlen(*str) && (*str)[*pos] != ' ' && (*str)[*pos])
		ft_putchar_fd((*str)[(*pos)++], 0);
}

void		ft_read_move(char **str, int c, size_t *pos, t_sys *sys)
{
	ft_print(*str, *pos, 0);
	if (c == sys->keymap[KEY_LEF] && *pos > 0)
	{
		ft_putchar_fd('\b', 0);
		*pos = *pos - 1;
	}
	if (c == sys->keymap[KEY_HOM] && *pos > 0)
	{
		ft_putchar_fd('\r', 0);
		*pos = 0;
	}
	if (c == sys->keymap[KEY_RIG] && *pos < ft_strlen(*str))
		ft_putchar_fd((*str)[(*pos)++], 0);
	while (c == sys->keymap[KEY_ENS] && *pos < ft_strlen(*str))
		ft_putchar_fd((*str)[(*pos)++], 0);
	if (c == sys->keymap[KEY_OLE])
		ft_read_keyole(&(*str), &(*pos));
	if (c == sys->keymap[KEY_ORI])
		ft_read_keyori(&(*str), &(*pos));
}
