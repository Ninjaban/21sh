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

static int		ft_count_fd(char *str)
{
	int		nbr;
	int		n;

	nbr = 0;
	n = 0;
	while (str[n])
	{
		if (ft_strncmp(str + n, ">&", 1) == 0)
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
		if (ft_strncmp(str + n, ">&", 1) == 0 &&
				(ft_isdigit(str[n + 2]) || str[n + 2] == '-') &&
				(n == 0 || str[n - 1] == ' ' || ft_isdigit(str[n - 1])))
		{
			while (n > 0 && ft_isdigit(str[n - 1]))
				n = n - 1;
			return (n);
		}
		if (str[n])
			n = n + 1;
	}
	return (n);
}

static char		*ft_read_color_fd_boucle(char *str, char *new, size_t i)
{
	size_t		n;
	size_t		next;

	n = 0;
	while (str[i])
	{
		next = ft_get_next_word(str, i);
		while (i < next)
			new[n++] = str[i++];
		if (str[i])
		{
			ft_strcopy_color(&new, "\x1b[38;5;88m", &n);
			while (ft_isdigit(str[i]))
				new[n++] = str[i++];
			new[n++] = str[i++];
			new[n++] = str[i++];
			if (str[i] == '-')
				new[n++] = str[i++];
			else
				while (ft_isdigit(str[i]))
					new[n++] = str[i++];
			ft_strcopy_color(&new, "\033[0m", &n);
		}
	}
	return (new);
}

char			*ft_read_color_fd(char *str)
{
	char	*new;

	if ((new = ft_strnew(ft_strlen(str) + (ft_count_fd(str) *
			(ft_strlen("\x1b[38;5;88m") + ft_strlen("\033[0m"))) + 1)) == NULL)
		return (NULL);
	new = ft_read_color_fd_boucle(str, new, 0);
	free(str);
	return (new);
}
