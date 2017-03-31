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

static void	ft_read_completion(char **str, char c, size_t *pos, t_sys **sys)
{
	ft_completion(&(*str), (c == (*sys)->keymap[KEY_TAB]) ? (*pos) : (*pos) + 1,
					(*sys)->env, (c == (*sys)->keymap[KEY_TAB]) ? 1 : 0);
	ft_print(*str, (*pos), (c == (*sys)->keymap[KEY_TAB]) ? 0 : 1);
	if (c != (*sys)->keymap[KEY_TAB])
		*pos = *pos + 1;
	else
		ft_read_keyori(&(*str), &(*pos));
}

static void	ft_read_check_completion(char **str, size_t *pos, t_sys **sys)
{
	ft_completion(&(*str), (*pos), (*sys)->env, 0);
	ft_print(*str, (*pos), 0);
}

static void	ft_read_check_suite(int c, char **str, t_sys **sys, size_t *n)
{
	static char	cpy = FALSE;

	if (c == (*sys)->keymap[KEY_BAC])
		ft_read_delete(&(*str), &(*n));
	if (c == (*sys)->keymap[KEY_DEL])
		ft_read_suppr(&(*str), &(*n));
	if (c == (*sys)->keymap[KEY_PST])
		ft_read_cpy_past(&(*str), &(*n), FALSE, FALSE);
	if (c == (*sys)->keymap[KEY_RST])
		ft_read_keymap_init(&(*sys));
	if (c == (*sys)->keymap[KEY_HOM] || c == (*sys)->keymap[KEY_ENS] ||
		c == (*sys)->keymap[KEY_LEF] || c == (*sys)->keymap[KEY_RIG] ||
		c == (*sys)->keymap[KEY_OLE] || c == (*sys)->keymap[KEY_ORI])
		ft_read_move(&(*str), c, &(*n), (*sys));
	if (c == (*sys)->keymap[KEY_CPY])
	{
		ft_read_cpy_past(&(*str), &(*n), TRUE, (cpy) ? FALSE : TRUE);
		ft_read_suppr(&(*str), &(*n));
		cpy = TRUE;
	}
	else
		cpy = FALSE;
}

char		ft_read_check(int c, char **str, t_sys **sys, size_t *n)
{
	static char	autocompl = TRUE;

	if (c == (*sys)->keymap[KEY_RET])
		return (TRUE);
	if (c == (*sys)->keymap[KEY_CPL])
	{
		autocompl = (autocompl == TRUE) ? FALSE : TRUE;
		if (autocompl == TRUE)
			ft_read_check_completion(&(*str), &(*n), &(*sys));
		else
			ft_print(*str, (*n), 0);
	}
	if ((ft_isprint(c) && c != (*sys)->keymap[KEY_TAB]) ||
		(c == (*sys)->keymap[KEY_TAB] && autocompl == TRUE))
	{
		ft_read_print(&(*str), c, &(*n), &(*sys));
		if (autocompl == TRUE)
			ft_read_completion(&(*str), c, &(*n), &(*sys));
		else
			ft_print(*str, (*n)++, 1);
	}
	ft_read_check_suite(c, &(*str), &(*sys), &(*n));
	return (FALSE);
}
