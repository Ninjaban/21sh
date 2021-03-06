/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 09:33:43 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/18 11:46:21 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "terms.h"

size_t		g_position;
size_t		g_nb;
size_t		g_limit;
char		**g_line;
char		**g_env;
char		**g_shvar;

void		ft_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	ft_print(*g_line, g_position, (int)(ft_strlen(*g_line) - g_position), TRUE);
	ft_putendl_fd("^C", 0);
	ft_affprompt(g_nb, g_env, g_shvar);
	if (g_line)
	{
		free(*g_line);
		*g_line = ft_strnew(1);
		g_position = 0;
	}
}

void		ft_sigwinch(int sig)
{
	struct winsize	window;

	if (sig != SIGWINCH)
		return ;
	ioctl(0, TIOCGWINSZ, &window);
	if (window.ws_row && ((window.ws_row - 1) * window.ws_col))
		g_limit = (size_t)((window.ws_row - 1) * window.ws_col - 1);
	else
		g_limit = 0;
	ft_print(*g_line, g_position, 0, FALSE);
}

void		ft_print(char *str, size_t pos, int inc, char resetstatic)
{
	static size_t	len_s = 0;
	char			*tmp;
	int				n;
	int				i;

	if ((tmp = ft_strnew(pos + (len_s * 2) + 3)) == NULL)
		return ;
	n = 0;
	while (pos && n < ((pos - 1 < g_limit) ? (int)pos - 1 : (int)g_limit - 1))
		tmp[n++] = '\b';
	i = 0;
	len_s = (len_s < g_limit) ? len_s : g_limit;
	while (i < (int)len_s)
		tmp[n + i++] = ' ';
	while (len_s > 0)
		tmp[n + i + len_s--] = '\b';
	tmp[n + i] = '\b';
	ft_print_norme(&tmp, pos, inc);
	len_s = (ft_checkcompl(str) == 1) ? ft_strlen(str) - 19 : ft_strlen(str);
	ft_read_color_main(str, pos + inc, g_limit);
	if (resetstatic)
		len_s = 0;
}

static void	ft_read_glob_init(size_t n, t_sys **sys)
{
	struct winsize	window;

	g_nb = n;
	g_env = (*sys)->env;
	g_shvar = (*sys)->shvar;
	g_position = 0;
	signal(SIGWINCH, &ft_sigwinch);
	ioctl(0, TIOCGWINSZ, &window);
	g_limit = (size_t)((window.ws_row - 1) * window.ws_col - 1);
}

int			ft_read(char **str, t_sys **sys, size_t n, char exit)
{
	size_t	i;
	int		c;

	ft_read_glob_init(n, sys);
	i = (size_t)ft_list_size((*sys)->history);
	*str = ft_strnew(1);
	g_line = &(*str);
	while (exit == FALSE)
	{
		c = 0;
		read(0, &c, sizeof(int));
		ft_removecompl(&(*str));
		exit = ft_read_check(c, &(*str), &(*sys), &g_position);
		if (c == (*sys)->keymap[KEY_EOF] && !ft_strlen(*str))
			return (FALSE);
		if (c == (*sys)->keymap[KEY_UPS])
			ft_read_history_up(&(*str), &(*sys), &i, &g_position);
		if (c == (*sys)->keymap[KEY_DOW])
			ft_read_history_do(&(*str), &(*sys), &i, &g_position);
	}
	ft_print(*str, g_position, (int)(ft_strlen(*str) - g_position), TRUE);
	ft_putchar_fd('\n', 0);
	signal(SIGWINCH, SIG_IGN);
	return (TRUE);
}
