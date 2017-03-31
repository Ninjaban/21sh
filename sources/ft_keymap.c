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

static void	ft_key_print_type(size_t key)
{
	char	*str;

	str = NULL;
	str = (key == KEY_EOF) ? "EOF		" : str;
	str = (key == KEY_TAB) ? "TAB		" : str;
	str = (key == KEY_RET) ? "RET		" : str;
	str = (key == KEY_BAC) ? "BACK		" : str;
	str = (key == KEY_DEL) ? "DEL		" : str;
	str = (key == KEY_CPY) ? "COPY		" : str;
	str = (key == KEY_PST) ? "PAST		" : str;
	str = (key == KEY_UPS) ? "UP		" : str;
	str = (key == KEY_DOW) ? "DOWN		" : str;
	str = (key == KEY_RIG) ? "RIGHT		" : str;
	str = (key == KEY_LEF) ? "LEFT		" : str;
	str = (key == KEY_HOM) ? "START		" : str;
	str = (key == KEY_ENS) ? "END		" : str;
	str = (key == KEY_OLE) ? "W-LEFT		" : str;
	str = (key == KEY_ORI) ? "W-RIGHT		" : str;
	str = (key == KEY_RST) ? "RESET		" : str;
	str = (key == KEY_CPL) ? "AUTO-COMPLETION	" : str;
	if (str)
		ft_putstr(str);
}

static void	ft_key_print_value(int value, char *str)
{
	str = (value == KEY_TAB_DEF) ? "TABULATION" : str;
	str = (value == KEY_DEL_DEF) ? "ERASE" : str;
	str = (value == KEY_RET_DEF) ? "RETURN" : str;
	str = (value == KEY_UPS_DEF) ? "FLÈCHE HAUT" : str;
	str = (value == KEY_DOW_DEF) ? "FLÈCHE BAS" : str;
	str = (value == KEY_LEF_DEF) ? "FLÈCHE GAUCHE" : str;
	str = (value == KEY_RIG_DEF) ? "FLÈCHE DROITE" : str;
	str = (value == KEY_HOM_DEF) ? "HOME" : str;
	str = (value == KEY_ENS_DEF) ? "END" : str;
	str = (value == KEY_BAC_DEF) ? "DELETE" : str;
	if (str)
	{
		ft_putstr("\e[33;1m");
		ft_putstr(str);
		ft_putstr("\e[0m");
	}
	else if (value >= 1 && value <= 29)
	{
		ft_putstr("\x1b[38;5;27mCTRL\e[0m - ");
		ft_putchar((char)value + 64);
	}
	else if (value >= 30 && value <= 255)
		ft_putchar(value);
}

static void	ft_keymap_print(int *keymap)
{
	size_t	n;

	n = 0;
	while (n < KEY_SIZE)
	{
		ft_putstr("\x1b[38;5;98m");
		ft_key_print_type(n);
		ft_putstr("\e[0m: ");
		ft_key_print_value(keymap[n], NULL);
		ft_putchar('\n');
		n = n + 1;
	}
}

char		ft_keymap(int **keymap, char **argv, t_sys *sys)
{
	if (argv[1] && ft_strcmp(argv[1], "--reset") == 0)
	{
		ft_keymap_reset(&(*keymap));
		return (TRUE);
	}
	if (argv[1] && ft_strcmp(argv[1], "--set") == 0)
		return (ft_keymap_set(&(*keymap), argv, sys));
	ft_keymap_print(*keymap);
	return (TRUE);
}
