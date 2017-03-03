/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:39:19 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/12 08:09:11 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static char	ft_parse_parenthesis_open(char *str, char type)
{
	size_t		n;

	n = 0;
	while (str[n] && str[n] != ((type == 0) ? '\"' : '\''))
		n = n + 1;
	if (str[n] != ((type == 0) ? '\"' : '\''))
		return (FALSE);
	str[n] = (type == 0) ? '\a' : '\t';
	return (TRUE);
}

void		ft_check_parenthesis(t_sys **sys, char **str, char *tmp, size_t n)
{
	char		*new;

	while ((*str)[n])
	{
		if ((((*str)[n] == '\"' || (*str)[n] == '\'')) &&
			((ft_parse_parenthesis_open((*str) + n + 1,
				((*str)[n] == '\"') ? 0 : 1) == FALSE)))
		{
			ft_putstr("<quotes>\n");
			if (ft_read(&tmp, &(*sys), 0) == FALSE)
				ft_log(TYPE_WARNING, ERROR_READ);
			new = ft_strjoin(((*str)[n] == '\"') ? "'\\n'" : "\\n", tmp);
			free(tmp);
			tmp = ft_strjoin(*str, new);
			free(new);
			free(*str);
			*str = tmp;
		}
		else
			n = n + 1;
	}
	n = 0;
	while ((*str)[++n])
		if ((*str)[n] == '\a' || (*str)[n] == '\t')
			(*str)[n] = ((*str)[n] == '\a') ? '\"' : '\'';
}
