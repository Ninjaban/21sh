/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 13:32:17 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/09 16:45:59 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "terms.h"

void		ft_read_keyole(char **str, size_t *pos)
{
	while (*pos > 0 && ft_isalnum((*str)[*pos]) == 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	while (*pos > 0 && ft_isalnum((*str)[*pos]) == 1)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
}

void		ft_read_keyori(char **str, size_t *pos)
{
	while (*pos < ft_strlen(*str) && ft_isalnum((*str)[*pos]) == 0)
		ft_putchar((*str)[(*pos)++]);
	while (*pos < ft_strlen(*str) && ft_isalnum((*str)[*pos]) == 1)
		ft_putchar((*str)[(*pos)++]);
}

void		ft_read_move(char **str, int c, size_t *pos)
{
	ft_print(*str, *pos, 0);
	if (c == KEY_LEF && *pos > 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	while (c == KEY_HOM && *pos > 0)
	{
		ft_putchar('\b');
		*pos = *pos - 1;
	}
	if (c == KEY_RIG && *pos < ft_strlen(*str))
		ft_putchar((*str)[(*pos)++]);
	while (c == KEY_ENS && *pos < ft_strlen(*str))
		ft_putchar((*str)[(*pos)++]);
	if (c == KEY_OLE)
		ft_read_keyole(&(*str), &(*pos));
	if (c == KEY_ORI)
		ft_read_keyori(&(*str), &(*pos));
}
