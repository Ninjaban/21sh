/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 13:14:08 by jcarra            #+#    #+#             */
/*   Updated: 2016/12/13 10:10:12 by jcarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

static int	ft_chdir_path(char *path, char ***env)
{
	if (ft_access_dir(path) == 1)
	{
		ft_set_pwd(&(*env), path);
		chdir(path);
		free(path);
		return (TRUE);
	}
	free(path);
	return (FALSE);
}

static int	ft_set_path(char **path, char *str)
{
	size_t	n;
	char	*tmp;

	if (ft_strcmp(str, "..") != 0)
		tmp = ft_path_join(*path, str);
	else
	{
		n = ft_strlen(*path);
		while (n > 0 && (*path)[n] != '/')
			n = n - 1;
		tmp = (n > 0) ? ft_strcut(*path, 0, n) : ft_strdup("/");
	}
	free(*path);
	*path = tmp;
	if (!tmp)
		return (FALSE);
	return (TRUE);
}

static int	ft_init_chdir_path(char **tab, char ***env)
{
	int		n;
	char	**path;

	n = -1;
	if ((path = ft_strsplit((*env)[ft_fpath((*env), "PWD")], "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	while (tab[++n])
		if ((ft_strcmp(tab[n], ".") != 0) &&
			(ft_set_path(&(path[1]), tab[n]) == FALSE))
		{
			ft_error(ERROR_ALLOC);
			return (FALSE);
		}
	ft_chdir_path(ft_strdup(path[1]), &(*env));
	ft_free_tab(path);
	return (TRUE);
}

static int	ft_old(char ***env)
{
	char	**old;

	if (ft_fpath((*env), "OLDPWD") == ft_tablen((*env)))
	{
		ft_error(ERROR_ENV);
		return (FALSE);
	}
	if ((old = ft_strsplit((*env)[ft_fpath((*env), "OLDPWD")], "=")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	if (ft_set_pwd(&(*env), old[1]) == FALSE)
	{
		ft_free_tab(old);
		return (FALSE);
	}
	chdir(old[1]);
	ft_free_tab(old);
	return (TRUE);
}

int			ft_chdir(char ***env, char *str)
{
	char		**tab;

	if (ft_fpath(*env, "PWD") == ft_tablen(*env))
	{
		ft_error(ERROR_ENV);
		return (FALSE);
	}
	if (!str)
		return (ft_chdir_path(ft_getenv(*env, "HOME"), &(*env)));
	if (ft_strcmp(str, "-") == 0)
		return (ft_old(&(*env)));
	if (str[0] == '/')
		return (ft_chdir_path(ft_strdup(str), &(*env)));
	if ((tab = ft_strsplit(str, "/")) == NULL)
	{
		ft_error(ERROR_ALLOC);
		return (FALSE);
	}
	ft_init_chdir_path(tab, &(*env));
	ft_free_tab(tab);
	return (TRUE);
}
