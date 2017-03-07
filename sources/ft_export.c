/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrajaona <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:05:48 by mrajaona          #+#    #+#             */
/*   Updated: 2017/03/07 11:54:03 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static size_t	ft_find_path(char **env, char *str)
{
	size_t		n;

	n = 0;
	while (env[n])
		if (ft_strncmp(env[n++], str, ft_strlen(str) - 1) == 0)
			return (n - 1);
	return (n);
}

static void		ft_change_var(char ***env, char *str, size_t n)
{
	char		*tmp;

	if ((tmp = ft_strdup(str)) == NULL)
		return (ft_error(ERROR_ALLOC));
	free((*env)[n]);
	(*env)[n] = tmp;
}

static void		ft_add_var(char ***env, char *str, size_t n)
{
	char	**tab;
	int		i;

	if ((tab = malloc(sizeof(char *) * (n + 2))) == NULL)
		return (ft_error(ERROR_ALLOC));
	i = -1;
	while ((*env)[++i])
		tab[i] = ft_strdup((*env)[i]);
	tab[i++] = ft_strdup(str);
	tab[i] = NULL;
	ft_free_tab(*env);
	*env = tab;
}

int				ft_export(char *str, char ***env, char ***shvar, int bool)
{
	char	**tab;
	size_t	n;

	if ((tab = ft_strsplit(str, "=")) == NULL)
	{
		ft_log(TYPE_ERROR, ERROR_ALLOC);
		return (FALSE);
	}
	if (ft_tablen(tab) == 1)
	{
		if ((n = ft_find_path(*shvar, tab[0])) != ft_tablen(*shvar))
		{
			ft_setenv((*shvar)[n], env, FALSE);
			ft_unsetenv(shvar, tab[0]);
			ft_free_tab(tab);
			if (bool == TRUE)
				free(str);
			return (TRUE);
		}
	}
	if (ft_tablen(tab) != 2)
	{
		ft_free_tab(tab);
		return (ft_error_int("ERROR_SYNTAX", FALSE));
	}
	if ((n = ft_find_path(*shvar, tab[0])) != ft_tablen(*shvar))
		ft_unsetenv(shvar, tab[0]);
	if ((n = ft_find_path(*env, tab[0])) != ft_tablen(*env))
		ft_change_var(&(*env), str, n);
	else
		ft_add_var(&(*env), str, n);
	ft_free_tab(tab);
	if (bool == TRUE)
		free(str);
	return (TRUE);
}
