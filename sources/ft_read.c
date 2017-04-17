/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 09:33:43 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/31 13:13:59 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "terms.h"

size_t		g_position;
size_t		g_nb;
size_t		limit;
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
	limit = (size_t)((window.ws_row - 1) * window.ws_col - 1);
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
	while (n < (int)pos - 1)
		tmp[n++] = '\b';
	i = 0;
	while (i < (int)len_s)
		tmp[n + i++] = ' ';
	while (len_s > 0)
		tmp[n + i + len_s--] = '\b';
	tmp[n + i] = '\b';
	if (!(pos || !inc))
		tmp[ft_strlen(tmp) - 1] = '\0';
	if (!(pos == 0 && inc == 0))
		ft_putstr_fd(tmp, 0);
	else
		ft_putstr_fd(" \b", 0);
	free(tmp);
	len_s = (ft_checkcompl(str) == 1) ? ft_strlen(str) - 19 : ft_strlen(str);
	n = (int)len_s;
	ft_read_color_main(str, limit);
	if (resetstatic)
		len_s = 0;
}

static void	ft_read_glob_init(size_t n, t_sys **sys)
{
	g_nb = n;
	g_env = (*sys)->env;
	g_shvar = (*sys)->shvar;
	g_position = 0;
	signal(SIGWINCH, &ft_sigwinch);
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
