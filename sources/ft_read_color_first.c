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

#include "shell.h"

static int		ft_count_separator(char *str)
{
	int		nbr;
	int		n;

	nbr = 1;
	n = 0;
	while (str[n])
	{
		if (str[n] == ';')
			nbr = nbr + 1;
		if (str[n] == '&' && str[n + 1] == '&')
			nbr = nbr + 1;
		if (str[n] == '|' && str[n + 1] == '|')
		{
			nbr = nbr + 1;
			n = n + 1;
		}
		else if (str[n] == '|')
			nbr = nbr + 1;
		n = n + 1;
	}
	return (nbr);
}

static size_t	ft_get_next_word(char *str, size_t n)
{
	char		separator;

	separator = FALSE;
	if (n == 0 && ft_isalnum(str[n]))
		return (n);
	while (str[n])
	{
		if (str[n] == '\x1b')
		{
			n = n + 1;
			while (str[n] != '\033')
				n = n + 1;
			while (str[n] != 'm')
				n = n + 1;
		}
		if ((str[n] == ';') || (str[n] == '&' && str[n + 1] == '&') ||
			(str[n] == '|' && str[n + 1] == '|') || (str[n] == '|'))
			separator = TRUE;
		if (ft_isalnum(str[n]) && separator == TRUE)
			return (n);
		n = n + 1;
	}
	return (n);
}

static char		*ft_read_color_first_boucle(char *str, char *new)
{
	size_t		n;
	size_t		i;
	size_t		next;

	n = 0;
	i = 0;
	while (str[i])
	{
		next = ft_get_next_word(str, i);
		while (i < next)
			new[n++] = str[i++];
		if (str[i])
		{
			ft_strcopy_color(&new, "\x1b[38;5;214m", &n);
			while (str[i] && ft_isalnum(str[i]))
				new[n++] = str[i++];
			ft_strcopy_color(&new, "\033[0m", &n);
		}
	}
	return (new);
}

char			*ft_read_color_first(char *str)
{
	char	*new;

	if ((new = ft_strnew(ft_strlen(str) + (ft_count_separator(str) *
			(ft_strlen("\x1b[38;5;214m") + ft_strlen("\033[0m"))) + 1)) == NULL)
		return (NULL);
	new = ft_read_color_first_boucle(str, new);
	free(str);
	return (new);
}
