/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 09:33:31 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 11:08:49 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# define EXIT_NO 0
# define EXIT_EC 1
# define EXIT_EN 2

# define TRUE 1
# define FALSE 0

# define KEY_RET 10
# define KEY_ESC 27
# define KEY_SPA 32
# define KEY_BAC 127
# define KEY_DEL 2117294875

# define KEY_UPS 4283163
# define KEY_DOW 4348699
# define KEY_RIG 4414235
# define KEY_LEF 4479771

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/ioctl.h>

typedef struct		s_data
{
	char			*name;
	char			b;
}					t_data;

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

typedef struct		s_win
{
	size_t			col;
	size_t			row;
	size_t			nbcol;
	size_t			sizecol;
}					t_win;

void				ft_add(t_list **begin, t_list *new);
void				ft_deldata(void *data);
void				ft_remove(t_list **list, int it, void (*f)(void *data));
void				ft_initlist(t_list **list, char **t, size_t len);
void				ft_display(t_win *win, t_list *list, int it);
void				ft_select(t_list *list);
void				ft_free_list(t_list *list);
void				ft_get_input(int *it, int *exit, t_win *win, t_list **list);
void				ft_print(t_list *list);
void				ft_sig_check(int signo);
int					ft_goto(char *cmd, int col, int line);
int					ft_termcaps_end(void);
int					ft_termcaps_init(void);
size_t				ft_get_maxsize(t_list *list);
size_t				ft_listlen(t_list *list);
t_data				*ft_newd(char *name);
t_list				*ft_new(void *data);
t_list				*ft_findit(t_list *list, int it);
t_list				*ft_listlast(t_list *begin);

#endif
