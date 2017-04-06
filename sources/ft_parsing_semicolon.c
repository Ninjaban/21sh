/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/01 12:00:00 by jcarra            #+#    #+#             */
/*   Updated: 2017/01/01 12:00:00 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "error.h"

static size_t	ft_parsing_semicolon_count(const char *str)
{
	size_t		nbr;
	size_t		n;

	nbr = 0;
	n = 0;
	while (str[n])
	{
		if (str[n] == ';' || str[n] == '>' ||
			str[n] == '<' || str[n] == '|' || str[n] == '&')
			nbr = nbr + 1;
		n = n + 1;
	}
	return (nbr);
}

static char		*ft_parsing_semicolon_new(const char *str)
{
	size_t	len;

	len = ft_strlen(str) + (ft_parsing_semicolon_count(str) * 2);
	return (ft_strnew(len + 1));
}

static void		ft_parsing_semicolon_suite(char **tmp, char *str,
											size_t *n, size_t *i)
{
	if (ft_strncmp(str + *n, ">&", 1) && ft_strncmp(str + *n, ">&", 1))
	{
		(*tmp)[(*i)++] = ' ';
		while (str[(*n)] == '<' || str[(*n)] == '>' ||
			   str[(*n)] == '|' || str[(*n)] == '&')
			(*tmp)[(*i)++] = str[(*n)++];
		(*tmp)[(*i)] = ' ';
		*n = *n - 1;
	}
	else
	{
		while (str[(*n)] == '<' || str[(*n)] == '>' ||
			   str[(*n)] == '|' || str[(*n)] == '&')
			(*tmp)[(*i)++] = str[(*n)++];
		*n = *n - 1;
		*i = *i - 1;
	}

}

static char		*ft_parsing_semicolon_copy(char *tmp, char *str,
											size_t n, size_t i)
{
	char		type;

	type = -1;
	while (str[n])
	{
		if ((str[n] == '\"' || str[n] == '\'') && type == -1)
			type = (str[n] == '\"') ? FALSE : TRUE;
		else if (type != -1 && (str[n] == '\"' || str[n] == '\''))
			type = ((type == FALSE && str[n] == '\"') ||
					(type == TRUE && str[n] == '\'')) ? -1 : type;
		if (str[n] == ';' && type == -1)
		{
			tmp[i++] = ' ';
			tmp[i++] = ';';
			tmp[i] = ' ';
		}
		else if ((str[n] == '<' || str[n] == '>' ||
				str[n] == '|' || str[n] == '&') && type == -1)
			ft_parsing_semicolon_suite(&tmp, str, &n, &i);
		else
			tmp[i] = str[n];
		i = i + 1;
		n = n + 1;
	}
	return (tmp);
}

char			*ft_parsing_semicolon(char *str)
{
	char	*tmp;

	if (str == NULL)
		return (str);
	if ((tmp = ft_parsing_semicolon_new(str)) == NULL)
		return (str);
	tmp = ft_parsing_semicolon_copy(tmp, str, 0, 0);
	free(str);
	return (tmp);
}
