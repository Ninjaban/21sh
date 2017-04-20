/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/18 17:32:34 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	ft_parse_backslash(char *str)
{
	size_t		n;

	n = 0;
	if ((str)[n + 1] == 'n')
		(str)[n] = '\n' * -1;
	else
		return ;
	n = n + 1;
	while ((str)[n++])
		(str)[n - 1] = (str)[n];
}

static void	ft_parse_parenthesis_change_char(char **src, size_t *n)
{
	char	type;

	type = ((*src)[(*n)++] == '\"') ? FALSE : TRUE;
	while ((*src)[*n] && (*src)[*n] != ((!type) ? '\"' : '\''))
	{
		(*src)[*n] = (char)((*src)[*n] * -1);
		if ((*src)[*n] == '\\' * -1 && (type == TRUE || type == FALSE))
			ft_parse_backslash(*src + *n);
		*n = *n + 1;
	}
}

void		ft_parse_parenthesis_open_init(char **src)
{
	size_t	i;

	i = 0;
	if (!src || !(*src))
		return ;
	while ((*src)[i])
	{
		if ((*src)[i] == '\"' || (*src)[i] == '\'')
			ft_parse_parenthesis_change_char(&(*src), &i);
		i = i + 1;
	}
}

void		ft_parse_parenthesis(char **str)
{
	size_t		n;
	char		type;

	n = 0;
	while ((*str)[n])
	{
		if ((*str)[n] == '\"' || (*str)[n] == '\'')
		{
			type = ((*str)[n] == '\"') ? FALSE : TRUE;
			ft_delchar(&(*str), n);
			while ((*str)[n] && (*str)[n] != ((!type) ? '\"' : '\''))
				n = n + 1;
			ft_delchar(&(*str), n);
		}
		else
			n = n + 1;
	}
}

void		ft_parenthesis_undo(char ***tab)
{
	size_t		n;
	size_t		i;

	n = 0;
	while ((*tab) && (*tab)[n])
	{
		i = 0;
		while ((*tab)[n][i])
		{
			if ((*tab)[n][i] < 0)
				(*tab)[n][i] = (char)((*tab)[n][i] * -1);
			i = i + 1;
		}
		n = n + 1;
	}
}
