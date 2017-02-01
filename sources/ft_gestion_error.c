/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 10:41:52 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/20 11:26:12 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int	ft_check(const char s, const char *c)
{
	int		n;

	n = 0;
	while (c[n] && c[n] != s)
		n = n + 1;
	return ((c[n] == s) ? 1 : 0);
}

static char	*ft_return(char *tmp)
{
	free(tmp);
	return (ERROR_SYNTAX);
}

char		*ft_gestion_error_init(char *str)
{
	size_t	n;
	char	**tab;
	char	*tmp;
	char	*new;

	n = 1;
	if ((tab = ft_strsplit(str, " \t")) == NULL)
		return (NULL);
	new = ft_strdup(tab[0]);
	while (tab[n])
	{
		tmp = ft_strjoin(new, tab[n++]);
		free(new);
		new = tmp;
	}
	ft_free_tab(tab);
	return (new);
}

void		*ft_gestion_error(char *str)
{
	size_t	n;
	char	*tmp;

	if ((tmp = ft_gestion_error_init(str)) == NULL)
		return (ERROR_ALLOC);
	n = 0;
	while (n < ft_strlen(tmp))
	{
		if (ft_check(tmp[n], "|&") == 1 && ft_check(tmp[n + 1], "|&<>") == 1)
			return (ft_return(tmp));
		n = n + 1;
	}
	n = 0;
	while (n < ft_strlen(tmp))
	{
		if (ft_check(tmp[n], "<>") == 1 &&
			(ft_check(tmp[n + 1], "|") == 1 || ft_check(tmp[n + 2], "<>") == 1))
			return (ft_return(tmp));
		n = n + 1;
	}
	if (ft_check(tmp[ft_strlen(tmp) - 1], "<>|") == 1)
		return (ft_return(tmp));
	free(tmp);
	return (NULL);
}
