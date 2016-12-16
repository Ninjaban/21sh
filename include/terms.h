/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:33:31 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/16 15:54:29 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# define KEY_TAB 9
# define KEY_RET 10
# define KEY_ESC 27
# define KEY_SPA 32
# define KEY_BAC 127
# define KEY_DEL 2117294875

# define KEY_UPS 4283163
# define KEY_DOW 4348699
# define KEY_RIG 4414235
# define KEY_LEF 4479771

# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

typedef struct		s_win
{
	size_t			col;
	size_t			row;
	size_t			nbcol;
	size_t			sizecol;
}					t_win;

int					fputchar(int c);
int					ft_goto(char *cmd, int col, int line);
int					ft_termcaps_change(struct termios *term);
int					ft_termcaps_init(struct termios *term, struct termios *save);
int					ft_read(char **str);

#endif
