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
#include "terms.h"

static void	ft_read_check_suite(int c, char **str, t_sys **sys, size_t *n)
{
	if (c == (*sys)->keymap[KEY_PST])
		ft_read_cpy_past(&(*str), &(*n), FALSE, FALSE);
	if (c == (*sys)->keymap[KEY_RST])
		ft_read_keymap_init(&(*sys));
}

char		ft_read_check(int c, char **str, t_sys **sys, size_t *n)
{
	static char	cpy = FALSE;

	if (c == (*sys)->keymap[KEY_RET])
		return (TRUE);
	if (ft_isprint(c) || c == (*sys)->keymap[KEY_TAB])
		ft_read_print(&(*str), c, &(*n), &(*sys));
	if (c == (*sys)->keymap[KEY_BAC])
		ft_read_delete(&(*str), &(*n));
	if (c == (*sys)->keymap[KEY_DEL])
		ft_read_suppr(&(*str), &(*n));
	if (c == (*sys)->keymap[KEY_HOM] || c == (*sys)->keymap[KEY_ENS] ||
		c == (*sys)->keymap[KEY_LEF] || c == (*sys)->keymap[KEY_RIG] ||
		c == (*sys)->keymap[KEY_OLE] || c == (*sys)->keymap[KEY_ORI])
		ft_read_move(&(*str), c, &(*n), (*sys));
	ft_read_check_suite(c, &(*str), &(*sys), &(*n));
	if (c == (*sys)->keymap[KEY_CPY])
	{
		ft_read_cpy_past(&(*str), &(*n), TRUE, (cpy) ? FALSE : TRUE);
		ft_read_suppr(&(*str), &(*n));
		cpy = TRUE;
	}
	else
		cpy = FALSE;
	return (FALSE);
}
