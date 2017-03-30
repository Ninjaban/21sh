/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:33:31 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/23 14:47:21 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMS_H
# define TERMS_H

# define KEY_EOF_DEF 4
# define KEY_TAB_DEF 9
# define KEY_RET_DEF 10
# define KEY_BAC_DEF 127
# define KEY_DEL_DEF 2117294875

# define KEY_CPY_DEF 11
# define KEY_PST_DEF 12

# define KEY_UPS_DEF 4283163
# define KEY_DOW_DEF 4348699
# define KEY_RIG_DEF 4414235
# define KEY_LEF_DEF 4479771
# define KEY_HOM_DEF 4741915
# define KEY_ENS_DEF 4610843
# define KEY_OLE_DEF 23
# define KEY_ORI_DEF 5
# define KEY_RST_DEF 16

# define KEY_EOF 0
# define KEY_TAB 1
# define KEY_RET 2
# define KEY_BAC 3
# define KEY_DEL 4

# define KEY_CPY 5
# define KEY_PST 6

# define KEY_UPS 7
# define KEY_DOW 8
# define KEY_RIG 9
# define KEY_LEF 10
# define KEY_HOM 11
# define KEY_ENS 12
# define KEY_OLE 13
# define KEY_ORI 14
# define KEY_RST 15

# define KEY_SIZE 16

# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

/*
** Todo : 1 fonction keymap init qui initialise les keymap par default
**
** Todo : 1 fonction keymap qui affiche des controle actuel.
**
** Todo : 1 fonction keymap --set qui prend en param 1 action sous forme de
** macro et qui demande a l'utilisateur le controle a associer, verifie si il
** n'est pas déjà utilisé, et l'associe dans ce cas, sinon, redemande un
** nouveau controle.
**
** Todo : 1 fonction keymap --reset qui remet les param des keymap par défault
** (voir les macro au dessus)
*/

/*
**	Keymap
*/

void				ft_keymap_reset(int **keymap);
char				ft_keymap_set(int **keymap, char **argv, t_sys *sys);
char				ft_keymap(int **keymap, char **argv, t_sys *sys);
int					*ft_keymap_init(void);

/*
**	Termcaps
*/

int					fputchar(int c);
int					ft_goto(char *cmd, int col, int line);
int					ft_termcaps_change(struct termios *term);
int					ft_termcaps_init(struct termios *term,
										struct termios *save);

#endif
