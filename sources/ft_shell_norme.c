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
			n = n + 1;
			while (str[n] && str[n] != ((type == FALSE) ? '\"' : '\''))
				n = n + 1;
			if (!str[n])
				return (type);
		}
		n = n + 1;
	}
	return (-1);
}

static char	ft_parse_parenthesis_open_init(char *src)
{
	char	*str;
	char	type;

	str = ft_strdup(src);
	if ((type = ft_parse_parenthesis_open_rec(str)) != -1)
	{
		free(str);
		return (type);
	}
	free(str);
	return (-1);
}

static void	ft_check_parenthesis(t_sys **sys, char **str)
{
	char		*new;
	char		*tmp;
	char		type;

	while ((type = ft_parse_parenthesis_open_init(*str)) != -1)
	{
		ft_putstr((type == FALSE) ? "<dquotes>\n" : "<quotes>\n");
		if (ft_read(&tmp, &(*sys), 0, FALSE) == FALSE)
			ft_log(TYPE_WARNING, ERROR_READ);
		if (type == FALSE &&
			(ft_strlen(*str) && (*str)[ft_strlen(*str) - 1] == '\\'))
		{
			(*str)[ft_strlen(*str) - 1] = '\0';
			new = ft_strdup(tmp);
		}
		else
			new = ft_strjoin("\\n", tmp);
		free(tmp);
		tmp = ft_strjoin(*str, new);
		free(new);
		free(*str);
		*str = tmp;
	}
}

void		ft_check_inhibitor(t_sys **sys, char **str)
{
	char		*new;
	char		*tmp;

	ft_check_parenthesis(&(*sys), &(*str));
	if (ft_strlen(*str))
		while ((*str)[ft_strlen(*str) - 1] == '\\')
		{
			ft_putstr("<backslash>\n");
			if (ft_read(&tmp, &(*sys), 0, FALSE) == FALSE)
				ft_log(TYPE_WARNING, ERROR_READ);
			(*str)[ft_strlen(*str) - 1] = '\0';
			new = ft_strjoin(*str, tmp);
			free(tmp);
			free(*str);
			*str = new;
			ft_check_parenthesis(&(*sys), &(*str));
		}
}
