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

void		ft_read_keyole(char **str, size_t *pos)
{
	if (*pos > 0 && (*str)[*pos - 1] == ' ')
	{
		ft_putchar_fd('\b', 0);
		*pos = *pos - 1;
	}
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
	size_t	n;

	n = ((*str)[*pos] && (*str)[*pos + 1] == ' ') ? 1 : 0;
	while (*pos + n < ft_strlen(*str) && (*str)[*pos + n] == ' ' &&
			(*str)[*pos + n])
		n = n + 1;
	while (*pos + n < ft_strlen(*str) && (*str)[*pos + n] != ' ' &&
			(*str)[*pos + n])
		n = n + 1;
	ft_print(*str, *pos, (int)n, FALSE);
	*pos = *pos + n;
}

void		ft_read_move(char **str, int c, size_t *pos, t_sys *sys)
{
	if (c == sys->keymap[KEY_RIG] || c == sys->keymap[KEY_ENS])
		ft_print(*str, *pos, (c == sys->keymap[KEY_RIG]) ? 1 :
							(int)ft_strlen(*str) - (int)*pos, FALSE);
	else
		ft_print(*str, *pos, 0, FALSE);
	if (c == sys->keymap[KEY_LEF] && *pos > 0)
	{
		ft_putchar_fd('\b', 0);
		*pos = *pos - 1;
	}
	while (c == sys->keymap[KEY_HOM] && *pos > 0)
	{
		ft_putchar_fd('\b', 0);
		*pos = *pos - 1;
	}
	if (c == sys->keymap[KEY_RIG] && *pos < ft_strlen(*str))
		*pos = *pos + 1;
	if (c == sys->keymap[KEY_ENS] && *pos < ft_strlen(*str))
		*pos = ft_strlen(*str);
	if (c == sys->keymap[KEY_OLE])
		ft_read_keyole(&(*str), &(*pos));
	if (c == sys->keymap[KEY_ORI])
		ft_read_keyori(&(*str), &(*pos));
}
