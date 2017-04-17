/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_limit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:40:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/17 16:40:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

size_t			ft_strlen_nocolor(char *str)
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

size_t			ft_getpos(char *str, size_t pos)
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

#include <stdio.h>

void		ft_strsetmax(char *str, size_t n, size_t pos, size_t limit)
{
	size_t	bs;

	if (pos > limit - 3)
		ft_putstr_fd("...", 0);
	if (ft_strlen_nocolor(str + n) < limit - 1)
		ft_putstr_fd(str + n, 0);
	else
	{
		if (pos > limit - 3)
			bs = ft_getpos(str + n, limit - 3);
		else
			bs = ft_getpos(str + n, limit);
//		write(0, str + n, limit - 3);
//		printf("%zu\n%zu\n%zu\n", ft_strlen_nocolor(str + n), limit - 3, ft_getpos(str + n, limit - 3));
//		bs = ft_getpos(str + n, limit - 3);
		str[bs + n - 1] = '\0';
//		printf("%zu\n", ft_strlen_nocolor(str + n));
		ft_putstr_fd(str + n, 0);
		ft_putstr_fd("\033[0m...\b\b\b", 0);
//		printf("%zu\n%zu\n", bs, pos - ft_strlen_nocolor(str));
	}
	bs = ft_strlen_nocolor(str + n) - 1;
	str[n] = '\0';
	while (bs-- > pos - ft_strlen_nocolor(str))
		ft_putchar_fd('\b', 0);
	free(str);
}

void		ft_putstr_limit(char *str, size_t pos, size_t limit)
{
	size_t	bs;

	if (ft_strlen_nocolor(str) <= limit)
	{
		ft_putstr_fd(str, 0);
		bs = ft_strlen_nocolor(str);
		while (bs-- > pos)
			ft_putchar_fd('\b', 0);
	}
	else if (limit > 20)
	{
//		if (pos > ft_strlen_nocolor(str) - 4)
//			ft_strsetmax(ft_strdup(str), (pos > limit) ? ft_getpos(str,
//						ft_strlen_nocolor(str) + 3 - limit) : 0, pos, limit);
//		else
		bs = (pos > limit - 3) ? ft_getpos(str, pos + 3 - (limit - 4)) : 0;
		ft_strsetmax(ft_strdup(str), bs, pos, limit);
	}
}