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

static int		ft_count_inhibitor(char *str)
{
	int		nbr;
	int		n;

	nbr = 0;
	n = 0;
	while (str[n])
	{
		if (str[n] == '\"' || str[n] == '\'')
			nbr = nbr + 1;
		n = n + 1;
	}
	return (nbr);
}

static size_t	ft_get_next_word(char *str, size_t n)
{
	while (str[n])
	{
		if (str[n] == '\x1b')
		{
			n = n + 1;
			while (str[n] && str[n] != '\033')
				n = n + 1;
			while (str[n] && str[n] != 'm')
				n = n + 1;
		}
		if (str[n] == '\"' || str[n] == '\'')
			return (n);
		if (str[n])
			n = n + 1;
	}
	return (n);
}

static char		*ft_read_color_inhibitor_boucle(char *str, char *new)
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
			ft_strcopy_color(&new, "\x1b[38;5;28m", &n);
			while (str[i] && (str[i] != str[next] || i == next))
				new[n++] = str[i++];
			if (str[i])
				new[n++] = str[i++];
			ft_strcopy_color(&new, "\033[0m", &n);
		}
	}
	return (new);
}

char			*ft_read_color_inhibitor(char *str)
{
	char	*new;

	if ((new = ft_strnew(ft_strlen(str) + (ft_count_inhibitor(str) *
			(ft_strlen("\x1b[38;5;28m") + ft_strlen("\033[0m"))) + 1)) == NULL)
		return (NULL);
	new = ft_read_color_inhibitor_boucle(str, new);
	free(str);
	return (new);
}
