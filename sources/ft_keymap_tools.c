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

#include "error.h"
#include "shell.h"
#include "terms.h"

static char	ft_keymap_check(int *keymap, int code, int macro)
{
	size_t	n;

	n = 0;
	while (n < KEY_SIZE)
		if (keymap[n++] == code && (int)n != macro)
			return (TRUE);
	return (FALSE);
}

void		ft_keymap_get(int **keymap, char macro, t_sys *sys)
{
	int		c;

	ft_log(TYPE_INFO, "Appuyez sur une touche : ");
	ft_termcaps_change(&sys->term_new);
	read(0, &c, sizeof(int));
	ft_termcaps_change(&sys->term_save);
	if (ft_keymap_check((*keymap), c, macro) == TRUE)
	{
		ft_log(TYPE_ERROR, "Cette touche est déjà utilisée.");
		ft_keymap_get(&(*keymap), macro, sys);
	}
	else
	{
		if ((c >= 1 && c <= 255) || c == KEY_TAB_DEF || c == KEY_BAC_DEF ||
			c == KEY_RET_DEF || c == KEY_DEL_DEF || c == KEY_UPS_DEF ||
			c == KEY_DOW_DEF || c == KEY_LEF_DEF || c == KEY_RIG_DEF ||
			c == KEY_HOM_DEF || c == KEY_ENS_DEF)
			(*keymap)[(int)macro] = c;
		else
		{
			ft_log(TYPE_ERROR, "Cette touche n'est pas utilisable.");
			ft_keymap_get(&(*keymap), macro, sys);
		}
	}
}

char		ft_keymap_set(int **keymap, char **argv, t_sys *sys)
{
	char	macro;

	macro = -1;
	macro = (!ft_strcmp(argv[2], "EOF")) ? (char)KEY_EOF : macro;
	macro = (!ft_strcmp(argv[2], "TAB")) ? (char)KEY_TAB : macro;
	macro = (!ft_strcmp(argv[2], "RET")) ? (char)KEY_RET : macro;
	macro = (!ft_strcmp(argv[2], "BACK")) ? (char)KEY_BAC : macro;
	macro = (!ft_strcmp(argv[2], "DEL")) ? (char)KEY_DEL : macro;
	macro = (!ft_strcmp(argv[2], "COPY")) ? (char)KEY_CPY : macro;
	macro = (!ft_strcmp(argv[2], "PAST")) ? (char)KEY_PST : macro;
	macro = (!ft_strcmp(argv[2], "UP")) ? (char)KEY_UPS : macro;
	macro = (!ft_strcmp(argv[2], "DOWN")) ? (char)KEY_DOW : macro;
	macro = (!ft_strcmp(argv[2], "RIGHT")) ? (char)KEY_RIG : macro;
	macro = (!ft_strcmp(argv[2], "LEFT")) ? (char)KEY_LEF : macro;
	macro = (!ft_strcmp(argv[2], "HOME")) ? (char)KEY_HOM : macro;
	macro = (!ft_strcmp(argv[2], "END")) ? (char)KEY_ENS : macro;
	macro = (!ft_strcmp(argv[2], "W-LEFT")) ? (char)KEY_OLE : macro;
	macro = (!ft_strcmp(argv[2], "W-RIGHT")) ? (char)KEY_ORI : macro;
	macro = (!ft_strcmp(argv[2], "RESET")) ? (char)KEY_RST : macro;
	macro = (!ft_strcmp(argv[2], "AUTO-COMPLETION")) ? (char)KEY_CPL : macro;
	if (macro == -1)
		return ((char)ft_error_int(ERROR_MACRO, FALSE));
	ft_keymap_get(&(*keymap), macro, sys);
	return (TRUE);
}

void		ft_keymap_reset(int **keymap)
{
	(*keymap)[KEY_EOF] = KEY_EOF_DEF;
	(*keymap)[KEY_TAB] = KEY_TAB_DEF;
	(*keymap)[KEY_RET] = KEY_RET_DEF;
	(*keymap)[KEY_BAC] = KEY_BAC_DEF;
	(*keymap)[KEY_DEL] = KEY_DEL_DEF;
	(*keymap)[KEY_CPY] = KEY_CPY_DEF;
	(*keymap)[KEY_PST] = KEY_PST_DEF;
	(*keymap)[KEY_UPS] = KEY_UPS_DEF;
	(*keymap)[KEY_DOW] = KEY_DOW_DEF;
	(*keymap)[KEY_RIG] = KEY_RIG_DEF;
	(*keymap)[KEY_LEF] = KEY_LEF_DEF;
	(*keymap)[KEY_HOM] = KEY_HOM_DEF;
	(*keymap)[KEY_ENS] = KEY_ENS_DEF;
	(*keymap)[KEY_OLE] = KEY_OLE_DEF;
	(*keymap)[KEY_ORI] = KEY_ORI_DEF;
	(*keymap)[KEY_RST] = KEY_RST_DEF;
	(*keymap)[KEY_CPL] = KEY_CPL_DEF;
}

int			*ft_keymap_init(void)
{
	int	*keymap;

	if ((keymap = malloc(sizeof(int *) * (KEY_SIZE + 1))) == NULL)
		return (NULL);
	keymap[KEY_SIZE] = 0;
	ft_keymap_reset(&keymap);
	return (keymap);
}
