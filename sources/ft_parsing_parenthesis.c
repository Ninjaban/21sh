/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:13:56 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/11 08:42:36 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void		ft_parse_backslash(char *str)
{
	size_t		n;

	n = 0;
	if ((str)[n + 1] == 'n')
		(str)[n] = '\n';
	else
		return ;
	n = n + 1;
	while ((str)[n++])
		(str)[n - 1] = (str)[n];
}

/*
static void		ft_parse_parenthesis_open(char *str, char c, char r, char type)
{
	size_t		n;

	n = 0;
	while (str[n] && str[n] != ((type == 0) ? '\"' : '\''))
	{
		if (str[n] == c)
			str[n] = r;
		if (type == 1 && str[n] == '\\' && c != r)
			ft_parse_backslash(str + n);
		n = n + 1;
	}
	while ((str)[n++])
		(str)[n - 1] = (str)[n];
}
*/
static char	ft_parse_parenthesis_open_check(char *str)
{
	size_t	n;

	n = 0;
	while (str[n])
	{
		if (str[n] == '\"' || str[n] == '\'')
			return (FALSE);
		n = n + 1;
	}
	return (TRUE);
}

static void	ft_parse_parenthesis_change_char(char **src, size_t n, char c,
												char r)
{
	char	type;

	type = ((*src)[n] == '\"') ? FALSE : TRUE;
	while ((*src)[n] && (*src)[n] != '\"' && (*src)[n] != '\'')
	{
		if ((*src)[n] == c)
			(*src)[n] = r;
		if ((*src)[n] == '\\' && type == TRUE)
			ft_parse_backslash(*src + n);
		n = n + 1;
	}
}

static char	ft_parse_parenthesis_open_rec(char **src, char *str, char c, char r)
{
	size_t	n;
	char	*lastchar;

	n = 0;
	lastchar = NULL;
	while (str[n])
	{
		if (str[n] == '\"' || str[n] == '\'')
		{
			if (!lastchar || str[n] != *lastchar)
				lastchar = str + n;
			else
			{
				ft_parse_parenthesis_change_char(&(*src), lastchar - str, c, r);
				*lastchar = '\a';
				str[n] = '\a';
				n = 0;
			}
		}
		n = n + 1;
	}
	return ((ft_parse_parenthesis_open_check(str)) ? TRUE : FALSE);
}

static char	ft_parse_parenthesis_open_init(char **src, char c, char r)
{
	char	*str;

	str = ft_strdup(*src);
	if (ft_parse_parenthesis_open_rec(&(*src), str, c, r) == FALSE)
	{
		free(str);
		return (FALSE);
	}
	free(str);
	return (TRUE);
}

void			ft_parse_parenthesis(char **str, char c, char r)
{
    size_t      n;

    n = 0;
	ft_parse_parenthesis_open_init(&(*str), c, r);
    while ((*str)[n])
    {
        if ((*str)[n] == '\"' || (*str)[n] == '\'')
            ft_delchar(&(*str), n);
        else
            n = n + 1;
    }
}

void			ft_parenthesis_undo(char ***tab)
{
	size_t		n;
	size_t		i;

	n = 0;
	while ((*tab) && (*tab)[n])
	{
		i = 0;
		while ((*tab)[n][i])
		{
			if ((*tab)[n][i] == '\a')
				(*tab)[n][i] = ' ';
			i = i + 1;
		}
		n = n + 1;
	}
}
