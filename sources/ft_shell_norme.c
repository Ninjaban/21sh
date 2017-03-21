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

static char	ft_parse_parenthesis_open_rec(char *str)
{
	size_t	n;
	char	type;

	n = 0;
	while (str[n])
	{
		if (str[n] == '\"' || str[n] == '\'')
		{
			type = (str[n] == '\"') ? FALSE : TRUE;
			while (str[n] && str[n] != ((!type) ? '\"' : '\''))
				n = n + 1;
			if (!str[n])
				return (FALSE);
		}
		n = n + 1;
	}
	return (TRUE);
}

static char	ft_parse_parenthesis_open_init(char *src)
{
	char	*str;

	str = ft_strdup(src);
	if (ft_parse_parenthesis_open_rec(str) == FALSE)
	{
		free(str);
		return (FALSE);
	}
	free(str);
	return (TRUE);
}

void		ft_check_parenthesis(t_sys **sys, char **str, char *tmp, size_t n)
{
	char		*new;

	while (ft_parse_parenthesis_open_init(*str) == FALSE)
	{
		ft_putendl_fd(*str, 0);
		ft_putstr("<quotes>\n");
		if (ft_read(&tmp, &(*sys), 0, FALSE) == FALSE)
			ft_log(TYPE_WARNING, ERROR_READ);
		new = ft_strjoin(((*str)[n] == '\"') ? "'\\n'" : "\\n", tmp);
		free(tmp);
		tmp = ft_strjoin(*str, new);
		free(new);
		free(*str);
		*str = tmp;
	}
	n = 0;
	while ((*str)[++n])
		if ((*str)[n] == '\a' || (*str)[n] == '\t')
			(*str)[n] = ((*str)[n] == '\a') ? '\"' : '\'';
}
