/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:33:31 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/17 09:50:26 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMS_H
# define TERMS_H

# define KEY_EOF 4
# define KEY_TAB 9
# define KEY_RET 10
# define KEY_BAC 127
# define KEY_DEL 2117294875

# define KEY_UPS 4283163
# define KEY_DOW 4348699
# define KEY_RIG 4414235
# define KEY_LEF 4479771
# define KEY_HOM 4741915
# define KEY_ENS 4610843
# define KEY_OLE 1146821403
# define KEY_ORI 1130044187

# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

int					fputchar(int c);
int					ft_goto(char *cmd, int col, int line);
int					ft_termcaps_change(struct termios *term);
int					ft_termcaps_init(struct termios *term,
										struct termios *save);

#endif
