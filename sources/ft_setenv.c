/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:06:46 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:09:03 by jcarra           ###   ########.fr       */
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
	{
		ft_error(ERROR_ALLOC);
		return ;
	}
	free((*env)[n]);
	(*env)[n] = tmp;
}

static void		ft_add_var(char ***env, char *str, size_t n)
{
	char	**tab;
	int		i;

	if ((tab = malloc(sizeof(char *) * (n + 2))) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return ;
	}
	i = -1;
	while ((*env)[++i])
		tab[i] = ft_strdup((*env)[i]);
	tab[i++] = ft_strdup(str);
	tab[i] = NULL;
	ft_free_tab(*env);
	*env = tab;
}

void			ft_setenv(char *str, char ***env, int bool)
{
	char	**tab;
	size_t	n;

	if ((tab = ft_strsplit(str, "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return ;
	}
	if (ft_tablen(tab) != 2)
	{
		ft_free_tab(tab);
		ft_error(ERROR_SYNTAX);
		return ;
	}
	if ((n = ft_find_path(*env, tab[0])) != ft_tablen(*env))
		ft_change_var(&(*env), str, n);
	else
		ft_add_var(&(*env), str, n);
	ft_free_tab(tab);
	if (bool == TRUE)
		free(str);
}
