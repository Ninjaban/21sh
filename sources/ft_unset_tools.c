/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 10:41:32 by jcarra            #+#    #+#             */
/*   Updated: 2017/04/13 11:36:42 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

size_t	ft_find_path(char **tab, char *str)
{
	size_t		n;

	n = 0;
	if (!tab)
		return (0);
	while (tab[n])
	{
		if (ft_strncmp(tab[n], str, ft_strlen(str) - 1) == 0)
		{
			if (tab[n][ft_strlen(str)] == '=')
				return (n);
		}
		n++;
	}
	return (n);
}

int		ft_del_line(char ***env, size_t i)
{
	char		**tab;
	size_t		n;
	size_t		j;

	j = 0;
	n = 0;
	if ((tab = malloc(sizeof(char *) * ft_tablen(*env))) == NULL)
		return (FALSE);
	while ((*env)[n])
	{
		if (n != i)
			tab[j++] = ft_strdup((*env)[n]);
		n = n + 1;
	}
	tab[j] = NULL;
	ft_free_tab(*env);
	(*env) = tab;
	return (TRUE);
}
