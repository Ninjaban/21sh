/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 22:06:46 by jcarra            #+#    #+#             */
/*   Updated: 2017/03/10 12:11:53 by mrajaona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

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

static int		ft_setenv_norme(char *str, char **tab, char ***env,
								char ***shvar)
{
	size_t	n;

	if (ft_tablen(tab) == 2)
	{
		if (shvar && (n = ft_find_path(*shvar, tab[0])) != ft_tablen(*shvar))
			ft_unsetenv(shvar, tab[0]);
		if ((n = ft_find_path(*env, tab[0])) != ft_tablen(*env))
			ft_change_var(&(*env), str, n);
		else
			ft_add_var(&(*env), str, n);
		return (TRUE);
	}
	else if (ft_tablen(tab) == 1 && shvar)
	{
		if ((n = ft_find_path(*shvar, tab[0])) != ft_tablen(*shvar))
		{
			ft_setenv((*shvar)[n], env, NULL, FALSE);
			ft_unsetenv(shvar, tab[0]);
			return (TRUE);
		}
	}
	else if (ft_tablen(tab) != 2)
		return (ft_error_int("ERROR_SYNTAX", FALSE));
	return (FALSE);
}

int				ft_setenv(char *str, char ***env, char ***shvar, int bool)
{
	char	**tab;
	int		ret;

	if (!str)
	{
		tab = ft_strsplit("env", " ");
		ft_env(tab, *env, shvar);
		ft_free_tab(tab);
		return (TRUE);
	}
	if ((tab = ft_strsplit(str, "=")) == NULL)
		return (ft_error_int(ERROR_ALLOC, FALSE));
	ret = ft_setenv_norme(str, tab, env, shvar);
	ft_free_tab(tab);
	if (bool == TRUE)
		free(str);
	return (ret);
}
