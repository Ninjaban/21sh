/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_limit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:40:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/18 17:18:45 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	ft_strlen_nocolor(char *str)
{
	size_t		n;
	size_t		len;

	n = 0;
	len = 0;
	while (str[n])
	{
		if (str[n] == '\033' || str[n] == '\x1b')
		{
			n = n + 1;
			while (str[n] && str[n - 1] != 'm')
				n = n + 1;
		}
		else
		{
			if (str[n] != '\a')
				len = len + 1;
			n = n + 1;
		}
	}
	return (len);
}

static size_t	ft_getpos(char *str, size_t pos)
{
	size_t		n;
	size_t		len;

	n = 0;
	len = 0;
	if (!pos)
		return (0);
	while (str[n])
	{
		if (str[n] == '\033' || str[n] == '\x1b')
		{
			n = n + 1;
			while (str[n] && str[n - 1] != 'm')
				n = n + 1;
		}
		else
		{
			if (str[n] != '\a')
				len = len + 1;
			if (pos == len)
				return (n);
			n = n + 1;
		}
	}
	return (n);
}

static void		ft_strsetmax(char *str, size_t n, size_t pos, size_t g_limit)
{
	size_t	bs;

	if (pos > g_limit - 3)
		ft_putstr_fd("...", 0);
	if (ft_strlen_nocolor(str + n) < g_limit - 3)
	{
		ft_putstr_fd(str + n, 0);
		bs = ft_strlen_nocolor(str + n);
	}
	else
	{
		if (pos > g_limit - 3)
			bs = ft_getpos(str + n, g_limit - 3);
		else
			bs = ft_getpos(str + n, g_limit - 0);
		str[bs + n - 1] = '\0';
		ft_putstr_fd(str + n, 0);
		ft_putstr_fd("\033[0m...\b\b\b", 0);
		bs = ft_strlen_nocolor(str + n) - 1;
	}
	str[n] = '\0';
	while (bs-- > pos - ft_strlen_nocolor(str))
		ft_putchar_fd('\b', 0);
	free(str);
}

void			ft_putstr_limit(char *str, size_t pos, size_t g_limit)
{
	size_t	bs;

	if (ft_strlen_nocolor(str) <= g_limit)
	{
		ft_putstr_fd(str, 0);
		ft_putstr_fd(" \b", 0);
		bs = ft_strlen_nocolor(str);
		while (bs-- > pos)
			ft_putchar_fd('\b', 0);
	}
	else if (g_limit > 20)
	{
		bs = (pos > g_limit - 3) ? ft_getpos(str, pos + 3 - (g_limit - 4)) : 0;
		ft_strsetmax(ft_strdup(str), bs, pos, g_limit);
	}
}
